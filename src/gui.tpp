// gui.cpp

#include "gui.h"

using namespace gui;

//! Converts Color to SDL_Color.
//
//! Useful to isolate SDL to other parts of the code.
SDL_Color Color::to_sdl_color() const
{
    unsigned char r, g, b, a;
    r = this->red * 0xff;
    g = this->green * 0xff;
    b = this->blue * 0xff;
    a = this->alpha * 0xff;

    SDL_Color s = { r, g, b, a };
    return s;
}

//! Default constructor.
Screen::Screen()
{ }

//! Starts up screen. 
//
//! @throws GuiException if something goes wrong.
//! @returns true if everything is OK.
bool Screen::start()
{
    //std::cerr << "Starting up GUI." << std::endl;
    SDL_Log( "Initialising SDL..." );

    // Initialize SDL.
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        SDL_Log( "Unable to initialise SDL." );
        throw GuiSdlException();
    }

    // Create window.
    this->window = SDL_CreateWindow(
        this->title.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        this->width,
        this->height,
        SDL_WINDOW_SHOWN
    );
    if( this->window == nullptr )
    {
        SDL_Log( "Failed to create window." );
        throw GuiSdlException();
    }

    // Create v-synced renderer for window.
    this->renderer = SDL_CreateRenderer(
        this->window,
        -1,
        //SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
        SDL_RENDERER_ACCELERATED
    );
    if( this->renderer == nullptr )
    {
        SDL_Log( "Failed to create renderer." );
        throw GuiSdlException();
    }

    // Initialize renderer color (black).
    SDL_Color c = this->background_color.to_sdl_color();
	SDL_SetRenderDrawColor( this->renderer, c.r, c.g, c.b, c.a );

    // Initialize SDL_ttf.
    if( TTF_Init() == -1 )
    {
        SDL_Log( "Failed to initialise fonts support." );
        throw GuiTtfException();
    }

    // Open the font.
	this->font = TTF_OpenFont( this->ttf_file, this->default_font_size );
	if( this->font == nullptr )
	{
        SDL_Log( "Failed to open font." );
        throw GuiTtfException();
	}

    // Get window surface.
    // this->surface = SDL_GetWindowSurface( window );

    // Ticks (to be able to count frame per second).
    this->start_ticks = SDL_GetTicks();

    // Start counting frames per second.
    this->num_frames = 0;
    this->fps = 0;

    return true;
}

//! Converts to string.
std::string Color::to_string() const
{
	return
		std::to_string( this->red ) + ", " +
		std::to_string( this->green ) + ", " +
		std::to_string( this->blue ) + ", " +
		std::to_string( this->alpha );
}

//! Destructor.
Screen::~Screen()
{ }

//! Shuts down screen.
void Screen::stop()
{
    std::cerr << "Shuting down screen." << std::endl;

    // Free font.
	TTF_CloseFont( this->font );
	this->font = nullptr;

	// Destroy window.
    SDL_DestroyRenderer( this->renderer );
	SDL_DestroyWindow( this->window );
    //SDL_FreeSurface( this->surface );
	this->window = nullptr;
    this->renderer = nullptr;
    //this->surface = nullptr;

	// Quit SDL subsystems.
    TTF_Quit();
	SDL_Quit();
}

//! Clears window with specified color.
//
//! @param color
void Screen::clear( Color color ) const
{
    // Specify color to the renderer.
    SDL_Color c = color.to_sdl_color();
    SDL_SetRenderDrawColor( this->renderer, c.r, c.g, c.b, c.a );

    // Clear screen with specified color.
    SDL_RenderClear( this->renderer );
}

//! Converts to screen coordinates.
//! @param cc --  Cartesian coordinates.
//! @return Screen coordinates relative to window_center.
Vec2i Screen::screen_coords( Vec2r cc ) const
{
    // On the screen, y coordinates are inverted !
    // Thus, you have to turn 180 degrees on the x axis.
    return (Vec2i) { (int) ( cc[0] * this->window_center.at(0) + this->window_center.at(0)),
                     (int) (-cc[1] * this->window_center.at(0) + this->window_center.at(1))};
}

//! Renders a point to the screen.
//! @param p -- coordinates on the screen.
//! @param c -- color of the point.
void Screen::render_point( Vec2r p, Color c ) const
{
    Vec2i sc = this->screen_coords( p );
    SDL_Color sdlc = c.to_sdl_color();
    SDL_SetRenderDrawColor( this->renderer, sdlc.r, sdlc.g, sdlc.b, sdlc.a );
    SDL_RenderDrawPoint( this->renderer, sc[0], sc[1] );
}

//! Rendes one line on the screen.
//! @param a, b -- two coordinates on the screen.
//! @param c -- color of the line.
//
// It just picks up one of the algorithms implemented below.
void Screen::render_line( Vec2r a, Vec2r b, Color c ) const
{
    // Set color.
    SDL_Color sdlc = c.to_sdl_color();
    SDL_SetRenderDrawColor( this->renderer, sdlc.r, sdlc.g, sdlc.b, sdlc.a );

    // Set coordinates.
    //Vec2i p0{(int) a.at(0),(int) a.at(1)};
    //Vec2i p1{(int) b.at(0),(int) b.at(1)};
    Vec2i p0 = this->screen_coords( a );
    Vec2i p1 = this->screen_coords( b );
    //cout << p0 << endl;
    // Draw.
    SDL_RenderDrawLine( this->renderer, p0[0], p0[1], p1[0], p1[1] );
}

inline void Screen::draw_point( int x , int y ) const
{
    SDL_RenderDrawPoint( this->renderer, x, y );
};

//! Renders a text to the screen.
//! @param pos -- position on the screen
//! @param text -- the text
//! @param color -- the color of the text
//! @throws GuiTtfException -- if cannot create texture for text.
void Screen::render_text( Vec2r pos, std::string text, Color color ) const
{
    // Render text surface.
    SDL_Surface* text_surface = TTF_RenderText_Shaded( this->font, text.c_str(), color.to_sdl_color(), black.to_sdl_color() );
    if( text_surface == nullptr )
    {
        throw GuiTtfException();
    }

    // Create texture from surface pixels.
    SDL_Texture* texture = SDL_CreateTextureFromSurface( this->renderer, text_surface );
	if( texture == nullptr )
    {
        throw GuiTtfException();
    }

    // Get size of the texture.
	SDL_Rect src_rect = { 0, 0, text_surface->w, text_surface->h };
    // Set size of the texture on screen.
    SDL_Rect dst_rect = { static_cast<int>(pos[0]), static_cast<int>(pos[1]), src_rect.w, src_rect.h };

    // Render texture to screen.
    SDL_RenderCopy( this->renderer, texture, &src_rect, &dst_rect );

    // Get rid of old surface.
    SDL_FreeSurface( text_surface );
    text_surface = nullptr;
    
    // Free texture.
	SDL_DestroyTexture( texture );
	texture = nullptr;
}

//! Updates screen.
void Screen::update()
{
    std::stringstream fps_text;

    // If one second has passed.
    if( SDL_GetTicks() - this->start_ticks >= 1000 )
    {
        // Take the number of frames and restart counting.
        this->fps = this->num_frames;
        this->start_ticks = SDL_GetTicks();
        this->num_frames = 0;
    }
    // Show fps.	
    fps_text.str( "" );
    fps_text << this->fps << " fps";
    // FIXME: take the position as argument?
    this->render_text( { 940, 10 }, fps_text.str().c_str(), white );

    // Update the surface.
    SDL_RenderPresent( this->renderer );
    ++num_frames;
}

// Returns exception message.
const char* GuiSdlException::what() const noexcept
{
    return SDL_GetError();
}

// Returns exception message.
const char* GuiTtfException::what() const noexcept
{
    return TTF_GetError();
}

inline int abs( int x ) { return x >=0 ? x : -x; }
inline int sgn( int x ) { return x >=0 ? 1 : -1; }
