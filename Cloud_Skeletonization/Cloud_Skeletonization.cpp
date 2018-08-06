// Cloud skeletonization project.

// Inclusions.

#include "Write_Input.h"
#include "Read_Input.h"
#include "Read_Cloud.h"
#include "Original_Graph.h"
#include "Find_Epsilon.h"
#include "Cloud_To_Nbhd_Graph.h"
#include "AlphaReeb_Algorithm.h"
#include "Simplify_Boost_Graph.h"
#include "Is_Homeomorphic.h"
#include "Geometric_Approximation_Error.h"
#include "Mapper.h"
#include "Hopes.h"
#include "Simplify_HoPeS.h"
#include "Simplify_HoPeS_2.h"
#include "Draw_Graph.h"
#include "Write_Image.h"
#include "Convert_Graph.h"
#include "Write_Graph.h"
#include "Check.h"
#include "Analysis.h"
#include "Read_Cloud_From_Image.h"
#include "Draw_Clouds.h"
#include "Print_Info.h"

// Global variables.

bool cloud_input = true;

bool write_input = true;

vector<int> wheel_range = { 3/*3, 4, 5, 6, 7, 8, 9, 10*/ };
vector<int> grid_cols_range = { /*1, 2, 3*/ };
vector<int> grid_rows_range = { /*1, 2, 3*/ };
vector<int> squares_range = { /*2, 3*/ };

bool graph_dependent_cloud_size = true;
int cloud_size_parameter = 100;

string noise_type = "uniform";
vector<double> noise_parameter_range = { 0.05, 0.2 };

bool alphaReeb = true;
vector<double> alpha_values = { 0.2/*0.1, 0.2, 0.3, 0.4, 0.5, 0.6*/ };
//double epsilon = 0.1;

bool mapper = true;
bool graph_dependent_num_intervals = true;
vector<double> num_intervals_parameter = { 1.4/*1, 1.2, 1.4, 1.6, 1.8, 2*/ };
double overlap_ratio = 0.5;
string filter_function = "Distance";
double sigma = 0.1;

double mcsf = 0.01;

bool hopes = true;

int repetitions = 10;

bool validation = false;

bool test = false;

// If test: wr 3; gdcp true; csp 100; nt uniform; npr 0.05; av 0.3; e 0.1; gdni true; nip 1.4; mcsf 0.01; r 5; v false.

bool image_input = false;

bool alphaReeb_on_image = true;

bool mapper_on_image = true;

bool hopes_on_image = true;

Run_Input run_input( wheel_range, grid_cols_range, grid_rows_range, squares_range, graph_dependent_cloud_size, cloud_size_parameter, noise_type, noise_parameter_range, alphaReeb, mapper, hopes, repetitions );

// Global constants.

const Scalar white = CV_RGB( 255, 255, 255 );
const Scalar black = CV_RGB( 0, 0, 0 );
const Scalar red = CV_RGB ( 255, 0, 0 );

// Directories.

const string root_directory = "/Users/philsmith/Documents/Xcode Projects/Cloud_Skeletonization/";
const string input_file = root_directory + "Input/Input.txt";
const string cloud_directory = root_directory + "Clouds/Txt_Files/";
const string image_directory = root_directory + "Code_Output/Images/";
const string graph_directory = root_directory + "Code_Output/Graphs/";
const string result_directory = root_directory + "Results/";
const string imported_image_directory = root_directory + "BSDS500/";

int main ( int, char*[] )
{
    clock_t start_time = clock(); // Start stopwatch.
    
    if (cloud_input) // Caries out algorithms on user-generated clouds.
    {
        if (write_input) Write_Input( input_file, run_input ); // Writing input.
        
        int experiment_iter = 0; // Counter for the number of experiments performed.
        
        ifstream ifs( input_file );
        string line_data;
        getline( ifs, line_data );
        
        while (getline( ifs, line_data )) // Looping over lines in the input file.
        {
            ++experiment_iter;
            
            Input input;
            
            Read_Input( line_data, input ); // Reading the input.
            
            size_t cloud_size = 0;
            
            vector<Results> alphaReeb_results( alpha_values.size() );
            for (int counter = 0; counter < alpha_values.size(); ++counter)
            {
                alphaReeb_results[counter].parameter = alpha_values[counter];
                alphaReeb_results[counter].time = 0;
                alphaReeb_results[counter].Betti_success.reserve( input.repetitions );
                alphaReeb_results[counter].homeo_success.reserve( input.repetitions );
                alphaReeb_results[counter].geom_approx_error.reserve( input.repetitions );
            }
            vector<Results> mapper_results( num_intervals_parameter.size() );
            for (int counter = 0; counter < num_intervals_parameter.size(); ++counter)
            {
                mapper_results[counter].parameter = num_intervals_parameter[counter];
                mapper_results[counter].time = 0;
                mapper_results[counter].Betti_success.reserve( input.repetitions );
                mapper_results[counter].homeo_success.reserve( input.repetitions );
                mapper_results[counter].geom_approx_error.reserve( input.repetitions );
            }
            Results hopes_results;
            hopes_results.Betti_success.reserve( input.repetitions );
            hopes_results.homeo_success.reserve( input.repetitions );
            hopes_results.geom_approx_error.reserve( input.repetitions );
            hopes_results.time = 0;
            
            for (int iteration = 0; iteration < input.repetitions; ++iteration) // Looping algorithm over clouds.
            {
                int expected_Betti_num;
                double graph_length;
                string diagonal_edges;
                vector<Data_Pt> cloud_d;
                vector<P2> cloud_p;
                
                Read_Cloud( cloud_directory, input, iteration, expected_Betti_num, graph_length, diagonal_edges, cloud_d ); // Reading the cloud.
                
                cloud_size += cloud_d.size();
                
                Convert_Cloud_1( cloud_d, cloud_p );
                
                Graph original_graph;
                
                Original_Graph( input.pattern_type, input.pattern_size_1, input.pattern_size_2, diagonal_edges, original_graph );
                
                bool draw_image = iteration % 50 == 0 || test ? true : false;
                
                if (input.alphaReeb) // Feeds cloud into the alpha-Reeb algorithm.
                {
                    double epsilon;
                    
                    Find_Epsilon( cloud_d, epsilon );
                    
                    if (epsilon > 0.125) epsilon = 0.125;
                    
                    Graph nbhd_graph;
                    
                    Cloud_To_Nbhd_Graph( cloud_d, epsilon, nbhd_graph ); // Generating the neighbourhood graph of the cloud.
                    
                    for (int counter = 0; counter < alpha_values.size(); ++counter) // Looping over alpha values.
                    {
                        input.alpha = alpha_values[counter];
                        AlphaReeb_Parameters parameters( input.alpha, mcsf );
                        
                        clock_t start_iter = clock(); // Start stopwatch for iteration.
                        
                        Graph alphaReeb_graph;
                        
                        AlphaReeb_Algorithm( nbhd_graph, parameters, alphaReeb_graph ); // Alpha-Reeb algorithm.
                        
                        clock_t end_iter = clock(); // Stop stopwatch for iteration.
                        
                        alphaReeb_results[counter].time += (end_iter - start_iter) * 1000 / (double)(CLOCKS_PER_SEC);
                        
                        Simplify_Boost_Graph( alphaReeb_graph );
                        
                        if (validation)
                        {
                            alphaReeb_results[counter].Betti_success.push_back( Check( expected_Betti_num, alphaReeb_graph ) ); // Seeing if expected and actual Betti numbers agree.
                            
                            alphaReeb_results[counter].homeo_success.push_back( Is_Homeomorphic( original_graph, alphaReeb_graph ) );
                            alphaReeb_results[counter].geom_approx_error.push_back( Geometric_Approximation_Error( alphaReeb_graph, cloud_p ) );
                        }
                        
                        if (draw_image)
                        {
                            const Point image_sizes( 800, 800 );
                            Mat image( image_sizes, CV_8UC3, white );
                            
                            Draw_Graph( alphaReeb_graph, 1, -1, 1, black, image ); // Drawing the output graph.
                            
                            Write_Image( image_directory, input, "AlphaReeb", iteration, image ); // Writing the image to a png file.
                        }
                        
                        Write_Graph( graph_directory, input, expected_Betti_num, graph_length, "AlphaReeb", iteration, alphaReeb_graph ); // Writing the graph to a txt file.
                    }
                }
                
                if (input.mapper) // Feeds cloud into Mapper.
                {
                    for (int counter = 0; counter < num_intervals_parameter.size(); ++counter) // Looping over number of intervals;
                    {
                        input.graph_dependent_num_intervals = graph_dependent_num_intervals;
                        
                        if (input.graph_dependent_num_intervals)
                        {
                            input.num_intervals_param = num_intervals_parameter[counter];
                            input.num_intervals = input.num_intervals_param * graph_length;
                        }
                        
                        else input.num_intervals = num_intervals_parameter[counter];
                        
                        Mapper_Parameters parameters( input.num_intervals, overlap_ratio, filter_function, sigma, mcsf );
                        
                        clock_t start_iter = clock(); // Start stopwatch for iteration.
                        
                        Graph mapper_graph;
                        
                        Mapper( cloud_d, parameters, mapper_graph ); // Generating the mapper graph.
                        
                        clock_t end_iter = clock(); // Stop stopwatch for iteration.
                        
                        mapper_results[counter].time += (end_iter - start_iter) * 1000 / (double)(CLOCKS_PER_SEC);
                        
                        Simplify_Boost_Graph( mapper_graph );
                        
                        if (validation)
                        {
                            mapper_results[counter].Betti_success.push_back( Check( expected_Betti_num, mapper_graph ) ); // Seeing if expected and actual Betti numbers agree.
                            
                            mapper_results[counter].homeo_success.push_back( Is_Homeomorphic( original_graph, mapper_graph ) );
                            mapper_results[counter].geom_approx_error.push_back( Geometric_Approximation_Error( mapper_graph, cloud_p ) );
                        }
                        
                        if (draw_image)
                        {
                            const Point image_sizes( 800, 800 );
                            Mat image( image_sizes, CV_8UC3, white );
                            
                            Draw_Graph( mapper_graph, 4, -1, 2, black, image ); // Drawing the output graph.
                            
                            Write_Image( image_directory, input, "Mapper", iteration, image ); // Writing the image to a png file.
                        }
                        
                        Write_Graph( graph_directory, input, expected_Betti_num, graph_length, "Mapper", iteration, mapper_graph ); // Writing the graph to a txt file.
                    }
                }
                
                if (input.hopes) // Carries out hopes algorithm.
                {
                    clock_t start_iter = clock(); // Start stopwatch for iteration.
                    
                    Graph_H hopes_graph;
                    double noise = 0;
                    
                    Hopes( cloud_p, hopes_graph, noise ); // Generating the Hopes graph.
                    
                    clock_t end_iter = clock(); // Stop stopwatch for iteration.
                    
                    hopes_results.time += (end_iter - start_iter) * 1000 / (double)(CLOCKS_PER_SEC);
                    
                    Simplify_HoPeS_2( hopes_graph );
                    
                    //Simplify_HoPeS( hopes_graph, 3 * noise );
                    
                    Graph hopes;
                    
                    Convert_Graph( hopes_graph, hopes );
                    
                    if (validation)
                    {
                        hopes_results.Betti_success.push_back( Check( expected_Betti_num, hopes ) ); // Seeing if expected and actual Betti numbers agree.
                        
                        hopes_results.homeo_success.push_back( Is_Homeomorphic( original_graph, hopes ) );
                        
                        hopes_results.geom_approx_error.push_back( Geometric_Approximation_Error( hopes, cloud_p ) );
                    }
                    
                    if (draw_image)
                    {
                        const Point image_sizes( 800, 800 );
                        Mat image( image_sizes, CV_8UC3, white );
                        
                        Draw_Graph( hopes_graph, black, red, image ); // Drawing the output graph.
                        
                        Write_Image( image_directory, input, "HoPeS1", iteration, image ); // Writing the image to a png file.
                    }
                    
                    Write_Graph( graph_directory, input, expected_Betti_num, graph_length, "HoPeS1", iteration, hopes ); // Writing the graph to a txt file.
                    
                    /*int counter = 0;
                    for (auto it = boost::vertices( hopes ).first; it != boost::vertices( hopes ).second; ++it, ++counter)
                    {
                        hopes[*it].index = counter;
                    }
                    
                    AlphaReeb_Parameters parameters( 0.2, 0.01 );
                    Graph haR;
                    
                    AlphaReeb( hopes, parameters, haR );
                    
                    Mat image_2( image_sizes, CV_8UC3, white );
                    
                    Draw_Graph( haR, 4, -1, 2, black, image_2 );
                    
                    imwrite( "/Users/philsmith/Documents/Xcode Projects/Cloud_Skeletonization/haR.png", image_2 );*/
                }
                
                cout << "Experiment " << experiment_iter << ": Iteration " << iteration << "." << endl;
            }
            
            size_t mean_cloud_size = cloud_size / input.repetitions;
            
            if (validation) Analysis( result_directory, input, mean_cloud_size, alphaReeb_results, mapper_results, hopes_results );
        }
        
        Print_Summary( start_time, experiment_iter ); // Printing summary.
    }
    
    if (image_input)
    {
        Mat InputImage;
        string image_name = "Woman"; // Woman, Bird_and_nest, Dog.
        
        InputImage = imread( imported_image_directory + image_name + ".jpg" );

        vector<vector<Data_Pt>> clouds;
        
        Read_Cloud_From_Image( imported_image_directory, image_name, InputImage, clouds );
        
        const Point image_sizes( 2 * InputImage.cols, 2 * InputImage.rows );
        Mat cloud_image( image_sizes, CV_8UC3, white );
        
        Draw_Clouds( clouds, cloud_image );
        
        imwrite( imported_image_directory + image_name + "_Cloud.png", cloud_image );
        
        if (hopes_on_image)
        {
            Mat hopes_image( image_sizes, CV_8UC3, white );
            
            vector<Graph_H> hopes_graph( clouds.size() );
            
            for (int counter = 0; counter < clouds.size(); ++counter)
            {
                vector<P2> converted_cloud;
                
                Convert_Cloud_1( clouds[counter], converted_cloud );
                double n = 0;
                Hopes( converted_cloud, hopes_graph[counter], n );
            }
            
            double scale = 2;
            Point2d shift = Point2d( 0, 0 );
            
            for (int counter = 0; counter < hopes_graph.size(); ++counter)
            {
                double scale_1 = 100;
                Point2d shift_1 = Point2d( 0, 0 );
                
                if (hopes_graph[counter].vertices.size() > 1)
                {
                    Scaling_Parameters( hopes_graph[counter], image_sizes, scale_1, shift_1 );
                }
                
                if (scale_1 < scale)
                {
                    //scale = scale_1;
                    //shift = shift_1;
                }
            }
            
            for (int counter = 0; counter < hopes_graph.size(); ++counter)
            {
                hopes_graph[counter].Draw( scale, shift, black, red, 1, hopes_image );
            }
            
            imwrite( imported_image_directory + image_name + "_Hopes.png", hopes_image );
            
            cout << "Completed hopes algorithm on image." << endl << endl;
        }
        
        if (alphaReeb_on_image)
        {
            Mat alphaReeb_image( image_sizes, CV_8UC3, white );
            
            vector<Graph> alphaReeb_graph( clouds.size() );
            
            for (int counter = 0; counter < clouds.size(); ++counter)
            {
                 double min_x = 1e10, min_y = 1e10, max_x = -1e10, max_y = -1e10;
                
                 for (auto p : clouds[counter])
                 {
                     if (p.pt.x < min_x) min_x = p.pt.x;
                     if (p.pt.x > max_x) max_x = p.pt.x;
                     if (p.pt.y < min_y) min_y = p.pt.y;
                     if (p.pt.y > max_y) max_y = p.pt.y;
                 }
                
                double epsilon = max( max_x - min_x, max_y - min_y ) * 0.05;
                
                Graph nbhd_graph;
                
                Cloud_To_Nbhd_Graph( clouds[counter], epsilon, nbhd_graph );
                
                AlphaReeb_Parameters parameters( 0.3, 0.01 );
                
                AlphaReeb_Algorithm( nbhd_graph, parameters, alphaReeb_graph[counter] );
            }
            
            double scale = 2;
            Point2d shift = Point2d( 0, 0 );
            
            for (int counter = 0; counter < alphaReeb_graph.size(); ++counter)
            {
                double scale_1 = 100;
                Point2d shift_1 = Point2d( 0, 0 );
                
                if (boost::num_vertices( alphaReeb_graph[counter] ) > 1)
                {
                    Scaling_Parameters( alphaReeb_graph[counter], image_sizes, scale_1, shift_1 );
                }
                
                if (scale_1 < scale)
                {
                    //scale = scale_1;
                    //shift = shift_1;
                }
            }
            
            for (int counter = 0; counter < alphaReeb_graph.size(); ++counter)
            {
                Draw_Vertices( alphaReeb_graph[counter], scale, shift, 1, -1, black, alphaReeb_image );
                
                Draw_Edges( alphaReeb_graph[counter], scale, shift, 1, black, alphaReeb_image );
            }
            
            imwrite( imported_image_directory + image_name + "_AlphaReeb.png", alphaReeb_image );
            
            cout << "Completed alpha-Reeb algorithm on image." << endl << endl;
        }
        
        if (mapper_on_image)
        {
            Mat mapper_image( image_sizes, CV_8UC3, white );
            
            vector<Graph> mapper_graph( clouds.size() );
            
            for (int counter = 0; counter < clouds.size(); ++counter)
            {
                Mapper_Parameters parameters( 15, 0.5, "Distance", 0.1, 0.01 );
                
                Mapper( clouds[counter], parameters, mapper_graph[counter] );
            }
            
            double scale = 2;
            Point2d shift = Point2d( 0, 0 );
            
            for (int counter = 0; counter < mapper_graph.size(); ++counter)
            {
                double scale_1 = 100;
                Point2d shift_1 = Point2d( 0, 0 );
                
                if (boost::num_vertices( mapper_graph[counter] ) > 1)
                {
                    Scaling_Parameters( mapper_graph[counter], image_sizes, scale_1, shift_1 );
                }
                
                if (scale_1 < scale)
                {
                    //scale = scale_1;
                    //shift = shift_1;
                }
            }
            
            for (int counter = 0; counter < mapper_graph.size(); ++counter)
            {
                Draw_Vertices( mapper_graph[counter], scale, shift, 1, -1, black, mapper_image );
                
                Draw_Edges( mapper_graph[counter], scale, shift, 1, black, mapper_image );
            }
            
            imwrite( imported_image_directory + image_name + "_Mapper.png", mapper_image );
            
            cout << "Completed mapper algorithm on image." << endl << endl;
        }
    }
    
    return 0;
}
