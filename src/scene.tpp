// scene.cpp

#include "scene.h"

//! Initializes the scene.
//
//! @param argc -- number of file names in the command line
//! @param argv -- the file names in the command line
//! @throws gui::GuiException if something goes wrong with the screen.
bool Scene::initialise( int argc, const char * argv[] )
{
    LOG_MSG( "Starting up scene.\n" );

    // Initialise game screen.
    this->screen = new Screen();
    this->screen->set_title( this->title );
    this->screen->set_width( this->win_width );
    this->screen->set_height( this->win_height );
    // TODO: implement this in the camera.
    //this->camera.set_image_width( this->get_win_width() );
    //this->camera.set_image_height( this->get_win_height() );

    // Create behaviors.
    this->quit_behavior = new Quit( *this );
    this->register_behavior( KEY_ESCAPE, this->quit_behavior );

    this->backward_behavior = new Backward( *this );
    this->register_behavior( KEY_DOWN, this->backward_behavior );
    this->forward_behavior = new Forward( *this );
    this->register_behavior( KEY_UP, this->forward_behavior );

    this->right_behavior = new Right( *this );
    this->register_behavior( KEY_RIGHT, this->right_behavior );
    this->left_behavior = new Left( *this );
    this->register_behavior( KEY_LEFT, this->left_behavior );


    // TODO: more behaviors: left, right, up, down, turn, etc.

    this->load_data( argc, argv );

    return this->screen->start();
}

//! Executes the application main loop.
void Scene::run_loop()
{
    while( this->running )
    {
        this->process_input();
        this->update();
        this->generate_output();
    }
}

//! Shuts down the scene.
void Scene::shutdown()
{
    // Destroy objects.
    this->unload_data();

    // Shuts down graphic interface.
    this->screen->stop();
}

//! Register behavior for corresponding event code.
void Scene::register_behavior( KeyCode code, IBehavior * behavior )
{
    this->key_state_behaviors.emplace( code, behavior );
}

//! Process keyboard and other inputs.
void Scene::process_input()
{
    SDL_Event event;

    // While there are events to be treated:
    while( SDL_PollEvent( &event ) )
    {
        switch( event.type )
        {
            case SDL_QUIT:
            {
                // Stops running the application.
                this->running = false;
                break;
            }
        }
    }

    // Get keyboard state.
    const Uint8 * keyboard_state = SDL_GetKeyboardState( NULL );
    // For each registered key state behavior:
    for( auto iter : this->key_state_behaviors )
    {
        // If corresponding key is pressed:
        if( keyboard_state[iter.first] )
        {
            // Start behavior.
            this->key_state_behaviors[iter.first]->start();
        }
        else
        {
            // Stop behavior.
            this->key_state_behaviors[iter.first]->stop();
        }
    }
}

//! Updates the scene.
void Scene::update()
{
    // Wait until min_frame_delay milliseconds has elapsed since last frame.
    //while( !SDL_TICKS_PASSED( SDL_GetTicks(), this->ticks_count + this->min_frame_delay ) );

    // Calculate delta time.
    // This is the difference in ticks from last frame (converted to seconds).
    float delta_time = (SDL_GetTicks() - this->ticks_count) / 1000.0f;

    // Update ticks count for next frame.
    this->ticks_count = SDL_GetTicks();

    // Clamp maximum delta time value.
    if( delta_time > delta_time_limit )
    {
        delta_time = delta_time_limit;
    }

    // Updates camera position, orientation and zoom.
    this->camera.update();
}

//! Generates output in the game.
void Scene::generate_output() const
{
    //DEBUG_MSG( "Entering Game::generate_output()\n" );

    // Clear screen.
    this->screen->clear( this->background_color );

    // Draw the scene.
    this->draw();

    // Show camera and frustum parameters.
    this->show_cam_params();
    this->show_fr_params();
    this->show_help();

    // Update screen.
    this->screen->update();
}
std::vector<string> split(const string& input, const string& regex) {
    std::regex re(regex);
    std::sregex_token_iterator
        first{input.begin(), input.end(), re, -1},
        last;
    return {first, last};
}
void Scene::load_obj_file( const char * file_name )
{
    ifstream fichier(file_name);
    std::string ligne;
    std::vector<std::string> line;

    std::vector<Point3r> vertices;
    std::vector<Vec3i> faces;
    int* f = new int[2];
    char t;
    float x,y,z;
    getline(fichier, ligne); // on retire la premiere ligne le nom
    while(getline(fichier, ligne)) //Tant qu'on n'est pas à la fin, on lit
    {
        fichier >> t;
        fichier >> x;
        fichier >> y;
        fichier >> z;
        if ( t=='v') 
        {
            
            Point<float,3> p(x,y,z);
            //cout << p<< endl;
            vertices.push_back(p);
            
        }
        else if ( t=='f')
        {
            Vec3i p{x,y,z};
            //cout << p << endl;
            faces.push_back(p);
        } 
       
    }
    
    this->objects.push_back(new Object3D(vertices,faces));
    //cout << "fin lecture" << endl;
    delete [] f;
    fichier.close();

}

//! Loads data to the scene.
void Scene::load_data( int argc, const char * argv[] )
{
    for ( int i =1 ; i< argc ; ++i)
    {
        this->load_obj_file(argv[i]);
    }
    this->draw_object(this->objects[0],0);
    
    // TODO:
    // Calls load_obj_file() to read all files passed on the command line.
    // and add objects to the scene.
    
}


//! Unloads data from the scene.
void Scene::unload_data()
{
   // Delete objects from the scene.
}

//! Draws the wireframe of all objects in the frustum.
void Scene::draw() const
{
    // TODO:
    // Draw objects.

    

    this->show_cam_params();
    this->show_fr_params();
}

void Scene::move_forward() { this->show_move_forward = true; camera.move_forward(); };
void Scene::stop_forward() { this->show_move_forward = false; camera.stop_forward(); };
void Scene::move_backward() { this->show_move_backward = true; camera.move_backward(); };
void Scene::stop_backward() { this->show_move_backward = false; camera.stop_backward(); };

void Scene::move_up() { this->show_move_up = true; camera.move_up(); };
void Scene::stop_up() { this->show_move_up = false; camera.stop_up(); };
void Scene::move_down() { this->show_move_down = true; camera.move_down(); };
void Scene::stop_down() { this->show_move_down = false; camera.stop_down(); };

void Scene::move_right() { this->show_move_right = true; camera.move_right(); };
void Scene::stop_right() { this->show_move_right = false; camera.stop_right(); };
void Scene::move_left() { this->show_move_left = true; camera.move_left(); };
void Scene::stop_left() { this->show_move_left = false; camera.stop_left(); };


//! Renders camera parameters.
void Scene::show_cam_params() const
{
    this->screen->render_text( { 10.0f, 10.0f }, "Camera", white );
    this->screen->render_text( { 10.0f, 25.0f }, "pos : ",white );//+this->camera.get_curr_pos().to_string(), white );
    this->screen->render_text( { 10.0f, 40.0f }, "ori : ",white );//+this->camera.get_curr_orient().to_string(), white );
    this->screen->render_text( { 10.0f, 55.0f }, "zoom: ",white );//+std::to_string( this->camera.get_curr_viewer_dist() ), white );
}

//! Renders frustum parameters.
void Scene::show_fr_params() const
{
    this->screen->render_text( { 700.0f,  10.0f }, "Frustum", white );
    this->screen->render_text( { 700.0f,  25.0f }, "near  : "/* + this->camera.frnear_to_string()*/, white );
    this->screen->render_text( { 700.0f,  40.0f }, "far   : "/* + this->camera.frfar_to_string( )*/, white );
    this->screen->render_text( { 700.0f,  55.0f }, "left  : "/* + this->camera.frleft_to_string( )*/, white );
    this->screen->render_text( { 700.0f,  70.0f }, "right : "/* + this->camera.frright_to_string( )*/, white );
    this->screen->render_text( { 700.0f,  85.0f }, "bottom: "/* + this->camera.frbottom_to_string( )*/, white );
    this->screen->render_text( { 700.0f, 100.0f }, "top   : "/* + this->camera.frtop_to_string( )*/, white );
}

//! Shows help on keyboard commands.
void Scene::show_help() const
{
    this->screen->render_text( {  10.0f, 748.0f }, "ESC: quit", white );
    this->screen->render_text( { 108.0f, 748.0f }, "UP: forward", this->show_move_forward ? green : white );
    this->screen->render_text( { 239.0f, 748.0f }, "DOWN: backward", this->show_move_backward ? green : white );
    this->screen->render_text( { 370.0f, 748.0f }, "RIGHT: right", this->show_move_right ? green : white );
    this->screen->render_text( { 501.0f, 748.0f }, "LEFT: left", this->show_move_left ? green : white );
    
    // TODO: add other keys...
}

//! Draws the wireframe of an object.
void Scene::draw_object( Object3D * const obj, float * zbuffer ) const
{
    // TODO:

    for ( int i=0; i < obj->num_faces() ; ++i)
    {
        this->draw_wire_triangle(obj->face(i));
    }
}

//! Draws the wireframe of a triangle.
void Scene::draw_wire_triangle( const Triangle & t ) const
{
    // TODO:
    this->screen->render_line(t.c0_1().begin_to_xy(),t.c0_1().end_to_xy(),white);
}

//! Draws an edge. (Used for wireframe drawings.)
//
//! @parm v0, v1 -- indexes of the line segment vertices.
void Scene::draw_edge( const Point<float, 4> & v0, const Point<float, 4>& v1 ) const
{
    // TODO:
}


//! Projects a point into the projection plane.
//
//! @return Point<float, 4> -- x,y are the position of the point in the plane.
//!                            z is its distance from the camera.
Point<float, 4> Scene::perspective_projection( const Point<float, 4> & p ) const
{
    // TODO:
}

// Quit behavior.
Quit::Quit( Scene & s ) : owner { s } {}
void Quit::start() const { this->owner.set_running( false ); }
void Quit::stop() const {}

// Backward behavior.
Backward::Backward( Scene & s ) : owner { s } {}
void Backward::start() const { this->owner.move_backward(); }
void Backward::stop() const { this->owner.stop_backward(); }

// Forward behavior.
Forward::Forward( Scene & s ) : owner { s } {}
void Forward::start() const { this->owner.move_forward(); }
void Forward::stop() const { this->owner.stop_forward(); }

// Up behavior.
Up::Up( Scene & s ) : owner { s } {}
void Up::start() const { this->owner.move_up(); }
void Up::stop() const { this->owner.stop_up(); }

// Down behavior.
Down::Down( Scene & s ) : owner { s } {}
void Down::start() const { this->owner.move_down(); }
void Down::stop() const { this->owner.stop_down(); }

// Right behavior.
Right::Right( Scene & s ) : owner { s } {}
void Right::start() const { this->owner.move_right(); }
void Right::stop() const { this->owner.stop_right(); }

// Left behavior.
Left::Left( Scene & s ) : owner { s } {}
void Left::start() const { this->owner.move_left(); }
void Left::stop() const { this->owner.stop_left(); }
