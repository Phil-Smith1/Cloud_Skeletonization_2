// Cloud skeletonization project.

// Inclusions.

#include "Write_Input.h"
#include "Read_Input.h"
#include "Read_Cloud.h"
#include "AlphaReeb.h"
#include "Mapper.h"
#include "Hopes.h"
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

bool test = false;

bool validation = true;

bool write_input = true;

vector<int> wheel_range = { /*3, 4, 5, 6,*/ 7, 8, 9, 10 };
vector<int> lattice_range = { /*1, 2, 3, 4*/ };
vector<int> row_range = { /*1, 2, 3, 4, 5*/ };
vector<int> concentric_squares_range = { /*2, 3*/ };

bool graph_dependent_cloud_size = true;
int cloud_size_parameter = 100;

string noise_type = "Gaussian";
double noise_parameter = 0.06;

bool alphaReeb = false;
vector<double> alpha_values = { 0.2, 0.3, 0.4, 0.5 };
double epsilon = 0.1;
// double min_comp_size_fraction;

bool mapper = true;
bool graph_dependent_num_intervals = true;
vector<double> num_intervals_parameter = { 1, 1.2, 1.4, 1.6, 1.8, 2 };
double overlap_ratio = 0.5;
string filter_function = "Distance";
double sigma = 0.1;
double min_comp_size_fraction = 0.01;

bool hopes = false;

int repetitions = 1000;

bool image_input = false;

bool alphaReeb_on_image = true;

bool mapper_on_image = true;

bool hopes_on_image = true;

Custom custom( test, wheel_range, lattice_range, row_range, concentric_squares_range, graph_dependent_cloud_size, cloud_size_parameter, noise_type, noise_parameter, alphaReeb, mapper, hopes, repetitions, alpha_values, epsilon, graph_dependent_num_intervals, num_intervals_parameter, overlap_ratio, filter_function, sigma, min_comp_size_fraction );

// Global constants.

const Scalar white = CV_RGB( 255, 255, 255 );
const Scalar black = CV_RGB( 0, 0, 0 );
const Scalar red = CV_RGB ( 255, 0, 0 );

// Directories.

const string root_directory = "/Users/philsmith/Documents/Xcode Projects/Cloud_Skeletonization/";
const string input_file = root_directory + "Input/Input.txt";
const string alphaReeb_parameter_file = root_directory + "Input/AlphaReeb_parameters.txt";
const string alpha_values_file = root_directory + "Input/Alpha_values.txt";
const string mapper_parameter_file = root_directory + "Input/Mapper_parameters.txt";
const string num_intervals_parameter_file = root_directory + "Input/Num_intervals_parameter.txt";
const string cloud_directory = root_directory + "Clouds/";
const string image_directory = root_directory + "Images/";
const string graph_directory = root_directory + "Graphs/";
const string result_directory = root_directory + "Results/";
const string imported_image_directory = root_directory + "BSDS500/";

int main ( int, char*[] )
{
    // Start stopwatch.
    
    clock_t start_time = clock();
    
    if (cloud_input) // Caries out algorithms on user-generated clouds.
    {
        // Write input.
        
        if (write_input) Write_Input( input_file, alphaReeb_parameter_file, alpha_values_file, mapper_parameter_file, num_intervals_parameter_file, custom );
        
        // Looping over lines in the input file.
        
        ifstream ifs( input_file );
        string line_data;
        getline( ifs, line_data );
        
        int experiment_iter = 0; // Counter for the number of experiments performed.
        
        while (getline( ifs, line_data ))
        {
            clock_t start_experiment = clock(); // Starts the stopwatch that measures the duration of the experiment.
            
            ++experiment_iter;
            
            // Reading the input.
            
            Input input;
            
            Read_Input( line_data, alphaReeb_parameter_file, alpha_values_file, mapper_parameter_file, num_intervals_parameter_file, experiment_iter, input );
            
            size_t cloud_size = 0;
            
            vector<pair<double, vector<bool>>> alphaReeb_results;
            vector<pair<double, vector<bool>>> mapper_results;
            vector<bool> hopes_results;
            vector<double> alphaReeb_time;
            vector<double> mapper_time;
            double hopes_time = 0;
            alphaReeb_results.clear();
            mapper_results.clear();
            hopes_results.clear();
            alphaReeb_time.clear();
            mapper_time.clear();
            alphaReeb_results.resize( input.alpha_values.size() );
            alphaReeb_time.resize( input.alpha_values.size() );
            mapper_results.resize( input.num_intervals_parameter.size() );
            mapper_time.resize( input.num_intervals_parameter.size() );
            
            for (int counter = 0; counter < input.alpha_values.size(); ++counter)
            {
                alphaReeb_results[counter].first = input.alpha_values[counter];
                alphaReeb_time[counter] = 0;
            }
            
            for (int counter = 0; counter < input.num_intervals_parameter.size(); ++counter)
            {
                mapper_results[counter].first = input.num_intervals_parameter[counter];
                mapper_time[counter] = 0;
            }
            
            // Looping algorithm over clouds.
            
            for (int iteration = 0; iteration < input.repetitions; ++iteration)
            {
                // Reading the cloud.
                
                int expected_Betti_num;
                double graph_length;
                
                vector<Data_Pt> cloud;
                cloud.clear();
                
                Read_Cloud( test, cloud_directory, input, iteration, expected_Betti_num, graph_length, cloud );
                
                cloud_size += cloud.size();
                
                if (input.alphaReeb) // Carries out alpha-Reeb algorithm.
                {
                    // Looping over alpha values.
                    
                    for (int counter = 0; counter < input.alpha_values.size(); ++counter)
                    {
                        clock_t start_iter = clock(); // Starts the stopwatch that measures the duration of the iteration.
                        
                        // Obtaining the parameters.
                        
                        input.alpha = input.alpha_values[counter];
                        
                        AlphaReeb_Parameters parameters( input.alpha, input.epsilon, input.min_comp_size_fraction );
                        
                        // Generating the alpha-Reeb graph.
                        
                        Graph alphaReeb_graph;
                        alphaReeb_graph.clear();
                        
                        AlphaReeb( cloud, parameters, alphaReeb_graph );
                        
                        // Drawing the output graph.
                        
                        const Point image_sizes( 800, 800 );
                        Mat image( image_sizes, CV_8UC3, white );
                        
                        Draw_Graph( alphaReeb_graph, 4, -1, 2, black, image );
                        
                        // Writing the image to a png file.
                        
                        if (test || iteration % 20 == 0) Write_Image( test, image_directory, input, "AlphaReeb", iteration, image );
                        
                        // Writing the graph to a txt file.
                        
                        Write_Graph( test, graph_directory, input, "AlphaReeb", iteration, alphaReeb_graph );
                        
                        // Seeing if expected and actual Betti numbers agree.
                        
                        if (validation) alphaReeb_results[counter].second.push_back( Check( expected_Betti_num, alphaReeb_graph ) );
                        
                        clock_t end_iter = clock(); // Stops the stopwatch that measures the duration of the iteration.
                        
                        alphaReeb_time[counter] += (end_iter - start_iter) * 1000 / (double)(CLOCKS_PER_SEC);
                    }
                }
                
                if (input.mapper) // Carries out mapper algorithm.
                {
                    // Looping over number of intervals;
                    
                    for (int counter = 0; counter < input.num_intervals_parameter.size(); ++counter)
                    {
                        clock_t start_iter = clock(); // Starts the stopwatch that measures the duration of the iteration.
                        
                        // Obtaining the parameters.
                        
                        if (input.graph_dependent_num_intervals)
                        {
                            input.num_intervals_param = input.num_intervals_parameter[counter];
                            input.num_intervals = input.num_intervals_param * graph_length;
                        }
                        
                        else input.num_intervals = input.num_intervals_parameter[counter];
                        
                        Mapper_Parameters parameters( input.num_intervals, input.overlap_ratio, input.filter_function, input.sigma, input.min_comp_size_fraction );
                        
                        // Generating the mapper graph.
                        
                        Graph mapper_graph;
                        mapper_graph.clear();
                        
                        Mapper( cloud, parameters, mapper_graph );
                        
                        // Drawing the output graph.
                        
                        const Point image_sizes( 800, 800 );
                        Mat image( image_sizes, CV_8UC3, white );
                        
                        Draw_Graph( mapper_graph, 4, -1, 2, black, image );
                        
                        // Writing the image to a png file.
                        
                        if (test || iteration % 20 == 0) Write_Image( test, image_directory, input, "Mapper", iteration, image );
                        
                        // Writing the graph to a txt file.
                        
                        Write_Graph( test, graph_directory, input, "Mapper", iteration, mapper_graph );
                        
                        // Seeing if expected and actual Betti numbers agree.
                        
                        if (validation) mapper_results[counter].second.push_back( Check( expected_Betti_num, mapper_graph ) );
                        
                        clock_t end_iter = clock(); // Stops the stopwatch that measures the duration of the iteration.
                        
                        mapper_time[counter] += (end_iter - start_iter) * 1000 / (double)(CLOCKS_PER_SEC);
                    }
                }
                
                if (input.hopes) // Carries out hopes algorithm.
                {
                    clock_t start_iter = clock(); // Starts the stopwatch that measures the duration of the iteration.
                    
                    // Generating the Hopes graph.
                    
                    Graph_H hopes_graph;
                    
                    Hopes( cloud, hopes_graph );
                    
                    // Drawing the output graph.
                    
                    const Point image_sizes( 800, 800 );
                    Mat image( image_sizes, CV_8UC3, white );
                    
                    Draw_Graph( hopes_graph, black, red, image );
                    
                    // Writing the image to a png file.
                    
                    if (test || iteration % 20 == 0) Write_Image( test, image_directory, input, "Hopes", iteration, image );
                    
                    // Writing the graph to a txt file.
                    
                    Graph hopes;
                    
                    Convert_Graph( hopes_graph, hopes );
                    
                    Write_Graph( test, graph_directory, input, "Hopes", iteration, hopes );
                    
                    // Seeing if expected and actual Betti numbers agree.
                    
                    if (validation) hopes_results.push_back( Check( expected_Betti_num, hopes ) );
                    
                    clock_t end_iter = clock(); // Stops the stopwatch that measures the duration of the iteration.
                    
                    hopes_time += (end_iter - start_iter) * 1000 / (double)(CLOCKS_PER_SEC);
                }
                
                if (iteration % 10 == 0) cout << iteration << endl;
            }
            
            size_t mean_cloud_size = cloud_size / input.repetitions;
            
            if (validation) Analysis( result_directory, input, mean_cloud_size, alphaReeb_results, mapper_results, hopes_results, alphaReeb_time, mapper_time, hopes_time );
            
            // Printing experiment summary.
            
            Print_Experiment_Summary( start_experiment, experiment_iter, input );
            
            if (test) break;
        }
        
        // Printing summary.
        
        Print_Summary( start_time, experiment_iter );
    }
    
    if (image_input)
    {
        string image_name = "Bird_and_nest"; // Woman, Bird_and_nest.
        
        vector<vector<Data_Pt>> clouds;
        clouds.clear();
        
        Read_Cloud_From_Image( imported_image_directory, image_name, clouds );
        
        const Point image_sizes( 800, 800 );
        Mat cloud_image( image_sizes, CV_8UC3, white );
        
        Draw_Clouds( clouds, cloud_image );
        
        imwrite( imported_image_directory + image_name + "_Cloud.png", cloud_image );
        
        if (hopes_on_image)
        {
            Mat hopes_image( image_sizes, CV_8UC3, white );
            
            vector<Graph_H> hopes_graph( clouds.size() );
            
            for (int counter = 0; counter < clouds.size(); ++counter)
            {
                Hopes( clouds[counter], hopes_graph[counter] );
            }
            
            double scale = 100;
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
                    scale = scale_1;
                    shift = shift_1;
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
                
                AlphaReeb_Parameters parameters( 0.3, epsilon, 0.01 );
                
                AlphaReeb( clouds[counter], parameters, alphaReeb_graph[counter] );
            }
            
            double scale = 100;
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
                    scale = scale_1;
                    shift = shift_1;
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
            
            double scale = 100;
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
                    scale = scale_1;
                    shift = shift_1;
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
