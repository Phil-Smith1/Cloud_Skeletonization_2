// Cloud skeletonization project.

// Inclusions.

#include "Write_Input.h"
#include "Read_Input.h"
#include "Initialise_Results.h"
#include "Read_Cloud.h"
#include "Original_Graph.h"
#include "Find_Epsilon.h"
#include "Cloud_To_Nbhd_Graph.h"
#include "AlphaReeb_Algorithm.h"
#include "Remove_Degree_1_Vertices.h"
#include "Simplify_Graph.h"
#include "Simplify_Graph_2.h"
#include "Is_Homeomorphic.h"
#include "Geometric_Approximation_Error.h"
#include "Mapper.h"
#include "Hopes.h"
#include "Simplify_HoPeS.h"
#include "Draw_Graph.h"
#include "Write_Image.h"
#include "Convert_Graph.h"
#include "Write_Graph.h"
#include "Check.h"
#include "Analysis.h"
#include "Read_Cloud_From_Image.h"
#include "Draw_Clouds.h"
#include "Print_Info.h"
#include "BSD_File.h"

// Global variables.

const bool cloud_input = true;

const bool write_input = true;

const vector<int> wheel_range = { /*3, 4, 5, 6, 7, 8, 9*/ };
const vector<int> grid_cols_range = { /*1, 2, 3*/ };
const vector<int> grid_rows_range = { /*1, 2, 3*/ };

const bool regular = true;

const vector<int> squares_range = { 4/*2, 3, 4, 5, 6, 7, 8, 9*/ };

const bool graph_dependent_cloud_size = true;
const int cloud_size_parameter = 100;

const string noise_type = "uniform";
const vector<double> noise_parameter_range = { 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4/*0.02, 0.04, 0.06, 0.08, 0.1, 0.12, 0.14, 0.16, 0.18, 0.2*/ };

const bool alphaReeb = true;
const vector<double> alpha_values = { 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6 };
const int alphaReeb_simp_type = 1; // 0: No simplification; 1: RD1V.

const bool mapper = true;
const bool graph_dependent_num_intervals = true;
const vector<double> num_intervals_parameter = { 1.5, 1.7, 1.9, 2.1, 2.3, 2.5, 2.7, 2.9, 3.1, 3.3 };
const vector<double> DBSCAN_parameter = { 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5 };
const double overlap_ratio = 0.5;
const string filter_function = "Distance";
const double sigma = 0.1;
const int mapper_simp_type = 1; // 0: No simplification; 1: RD1V.

const double mcsf = 0.05;

const bool hopes = true;
const int hopes_simp_type = 2; // 0: No simplification; 1: RD1V; 2: RD1V SH MD; 3: RD1V SH 2MD; 4: aR RD1V; 5: RD1V aR RD1V; 6: SH2.

const int repetitions = 200;

const bool validation = true;

const bool test = false;

// If test: wr 3; gdcp true; csp 100; nt uniform; npr 0.05; av 0.3; e 0.1; gdni true; nip 1.4; mcsf 0.01; r 5; v false.

const bool image_input = false;

const string image_name = "Woman"; // Woman, Bird_and_nest, Dog.

const bool alphaReeb_on_image = true;

const bool mapper_on_image = true;

const bool hopes_on_image = true;

const int hopes_simp_type_2 = 7;

const bool BSD = false;

Run_Input run_input( wheel_range, grid_cols_range, grid_rows_range, regular, squares_range, graph_dependent_cloud_size, cloud_size_parameter, noise_type, noise_parameter_range, alphaReeb, alphaReeb_simp_type, mapper, mapper_simp_type, hopes, hopes_simp_type, repetitions );

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
const string BSD_directory = root_directory + "BSDS500/";

int main ( int, char*[] )
{
    if (cloud_input) // Caries out algorithms on user-generated clouds.
    {
        clock_t start_time = clock(); // Start stopwatch.
        
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
            vector<Results> mapper_results( num_intervals_parameter.size() * DBSCAN_parameter.size() );
            Results hopes_results;
            
            Initialise_Results( alphaReeb_results, alpha_values, mapper_results, num_intervals_parameter, DBSCAN_parameter, hopes_results, input.repetitions );
            
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
                    
                    Find_Epsilon( cloud_p, epsilon );
                    
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
                        
                        Simplify_Graph( alphaReeb_graph, alphaReeb_simp_type );
                        
                        if (validation)
                        {
                            bool correct_Betti = Check( expected_Betti_num, alphaReeb_graph );
                            
                            alphaReeb_results[counter].Betti_success.push_back( correct_Betti );
                            
                            if (correct_Betti)
                            {
                                pair<double, double> gae_rms = Geometric_Approximation_Error( alphaReeb_graph, cloud_p );
                                
                                alphaReeb_results[counter].homeo_success.push_back( Is_Homeomorphic( original_graph, alphaReeb_graph ) );
                                alphaReeb_results[counter].geom_approx_error.push_back( gae_rms.first );
                                alphaReeb_results[counter].rms.push_back( gae_rms.second );
                            }
                        }
                        
                        if (draw_image)
                        {
                            const Point image_sizes( 800, 800 );
                            Mat image( image_sizes, CV_8UC3, white );
                            
                            Draw_Graph( alphaReeb_graph, 5, -1, 2, black, image ); // Drawing the output graph.
                            
                            Write_Image( image_directory, input, "AlphaReeb", iteration, image ); // Writing the image to a png file.
                        }
                        
                        Write_Graph( graph_directory, input, expected_Betti_num, graph_length, "AlphaReeb", iteration, alphaReeb_graph ); // Writing the graph to a txt file.
                    }
                }
                
                if (input.mapper) // Feeds cloud into Mapper.
                {
                    for (int counter_1 = 0; counter_1 < num_intervals_parameter.size(); ++counter_1) // Looping over number of intervals;
                    {
                        for (int counter_2 = 0; counter_2 < DBSCAN_parameter.size(); ++counter_2)
                        {
                            input.graph_dependent_num_intervals = graph_dependent_num_intervals;
                            
                            if (input.graph_dependent_num_intervals)
                            {
                                input.num_intervals_param = num_intervals_parameter[counter_1];
                                input.num_intervals = input.num_intervals_param * graph_length + 0.5;
                            }
                            
                            else input.num_intervals = num_intervals_parameter[counter_1];
                            
                            input.DBSCAN_parameter = DBSCAN_parameter[counter_2];
                            
                            Mapper_Parameters parameters( input.num_intervals, overlap_ratio, filter_function, sigma, input.DBSCAN_parameter, mcsf );
                            
                            clock_t start_iter = clock(); // Start stopwatch for iteration.
                            
                            Graph mapper_graph;
                            
                            Mapper( cloud_d, parameters, mapper_graph ); // Generating the mapper graph.
                            
                            clock_t end_iter = clock(); // Stop stopwatch for iteration.
                            
                            mapper_results[counter_1 * DBSCAN_parameter.size() + counter_2].time += (end_iter - start_iter) * 1000 / (double)(CLOCKS_PER_SEC);
                            
                            Simplify_Graph( mapper_graph, mapper_simp_type );
                            
                            if (validation)
                            {
                                bool correct_Betti = Check( expected_Betti_num, mapper_graph );
                                
                                mapper_results[counter_1 * DBSCAN_parameter.size() + counter_2].Betti_success.push_back( correct_Betti );
                                
                                if (correct_Betti)
                                {
                                    pair<double, double> gae_rms = Geometric_Approximation_Error( mapper_graph, cloud_p );
                                    
                                    mapper_results[counter_1 * DBSCAN_parameter.size() + counter_2].homeo_success.push_back( Is_Homeomorphic( original_graph, mapper_graph ) );
                                    mapper_results[counter_1 * DBSCAN_parameter.size() + counter_2].geom_approx_error.push_back( gae_rms.first );
                                    mapper_results[counter_1 * DBSCAN_parameter.size() + counter_2].rms.push_back( gae_rms.second );
                                }
                            }
                            
                            if (draw_image)
                            {
                                const Point image_sizes( 800, 800 );
                                Mat image( image_sizes, CV_8UC3, white );
                                
                                Draw_Graph( mapper_graph, 5, -1, 2, black, image ); // Drawing the output graph.
                                
                                Write_Image( image_directory, input, "Mapper", iteration, image ); // Writing the image to a png file.
                            }
                            
                            Write_Graph( graph_directory, input, expected_Betti_num, graph_length, "Mapper", iteration, mapper_graph ); // Writing the graph to a txt file.
                        }
                    }
                }
                
                if (input.hopes) // Carries out hopes algorithm.
                {
                    clock_t start_iter = clock(); // Start stopwatch for iteration.
                    
                    double max_birth = 0, min_death = 1e10;
                    Graph_H hopes_graph;
                    
                    Hopes( cloud_p, hopes_graph, max_birth, min_death ); // Generating the Hopes graph.
                    
                    clock_t end_iter = clock(); // Stop stopwatch for iteration.
                    
                    hopes_results.time += (end_iter - start_iter) * 1000 / (double)(CLOCKS_PER_SEC);
                    
                    Graph hopes;
                    
                    Simplify_Graph( hopes_graph, hopes_simp_type, min_death, mcsf, hopes );
                    
                    if (validation)
                    {
                        bool correct_Betti = Check( expected_Betti_num, hopes );
                        
                        hopes_results.Betti_success.push_back( correct_Betti );
                        
                        if (correct_Betti)
                        {
                            pair<double, double> gae_rms = Geometric_Approximation_Error( hopes, cloud_p );
                            
                            hopes_results.homeo_success.push_back( Is_Homeomorphic( original_graph, hopes ) );
                            hopes_results.geom_approx_error.push_back( gae_rms.first );
                            hopes_results.rms.push_back( gae_rms.second );
                        }
                    }
                    
                    if (draw_image)
                    {
                        const Point image_sizes( 800, 800 );
                        Mat image( image_sizes, CV_8UC3, white );
                        
                        if (hopes_simp_type <= 1) Draw_Graph( hopes_graph, black, red, image ); // Drawing the output graph.
                        
                        else Draw_Graph( hopes, 5, -1, 2, black, image );
                                                    
                        Write_Image( image_directory, input, "HoPeS1", iteration, image ); // Writing the image to a png file.
                    }
                    
                    Write_Graph( graph_directory, input, expected_Betti_num, graph_length, "HoPeS1", iteration, hopes ); // Writing the graph to a txt file.
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
        Mat input_image;
        
        input_image = imread( BSD_directory + image_name + "/" + image_name + ".jpg" );

        vector<vector<Data_Pt>> clouds;
        
        Read_Cloud_From_Image( BSD_directory, image_name, input_image, clouds );
        
        const Point image_sizes( 2 * input_image.cols, 2 * input_image.rows );
        Mat cloud_image( image_sizes, CV_8UC3, white );
        
        Draw_Clouds( clouds, cloud_image );
        
        imwrite( BSD_directory + image_name + "/" + image_name + "_Cloud.png", cloud_image );
        
        if (hopes_on_image)
        {
            Mat hopes_image( image_sizes, CV_8UC3, white );
            
            vector<Graph> hopes_graph( clouds.size() );
            
            for (int counter = 0; counter < clouds.size(); ++counter)
            {
                vector<P2> converted_cloud;
                
                Convert_Cloud_1( clouds[counter], converted_cloud );
                
                double max_birth = 0, min_death = 1e10;
                Graph_H g;
                
                Hopes( converted_cloud, g, max_birth, min_death );
                
                Simplify_Graph( g, hopes_simp_type_2, min_death, mcsf, hopes_graph[counter] );
            }
            
            double scale = 2;
            Point2d shift = Point2d( 0, 0 );
            
            for (int counter = 0; counter < hopes_graph.size(); ++counter)
            {
                Draw_Vertices( hopes_graph[counter], scale, shift, 2, -1, black, hopes_image );
                
                Draw_Edges( hopes_graph[counter], scale, shift, 2, black, hopes_image );
            }
            
            /*for (int counter = 0; counter < hopes_graph.size(); ++counter)
            {
                hopes_graph[counter].Draw( scale, shift, black, red, 1, hopes_image );
            }*/
            
            imwrite( BSD_directory + image_name + "/" + image_name + "_Hopes.png", hopes_image );
            
            cout << "Completed hopes algorithm on " << image_name << "." << endl << endl;
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
                
                AlphaReeb_Parameters parameters( 4, 0 );
                
                AlphaReeb_Algorithm( nbhd_graph, parameters, alphaReeb_graph[counter] );
            }
            
            double scale = 2;
            Point2d shift = Point2d( 0, 0 );
            
            for (int counter = 0; counter < alphaReeb_graph.size(); ++counter)
            {
                Draw_Vertices( alphaReeb_graph[counter], scale, shift, 2, -1, black, alphaReeb_image );
                
                Draw_Edges( alphaReeb_graph[counter], scale, shift, 2, black, alphaReeb_image );
            }
            
            imwrite( BSD_directory + image_name + "/" + image_name + "_AlphaReeb.png", alphaReeb_image );
            
            cout << "Completed alpha-Reeb algorithm on " << image_name << "." << endl << endl;
        }
        
        if (mapper_on_image)
        {
            Mat mapper_image( image_sizes, CV_8UC3, white );
            
            vector<Graph> mapper_graph( clouds.size() );
            
            for (int counter = 0; counter < clouds.size(); ++counter)
            {
                Mapper_Parameters parameters( 15, 0.5, "Distance", 0.1, 3, 0 );
                
                Mapper( clouds[counter], parameters, mapper_graph[counter] );
            }
            
            double scale = 2;
            Point2d shift = Point2d( 0, 0 );
            
            for (int counter = 0; counter < mapper_graph.size(); ++counter)
            {
                Draw_Vertices( mapper_graph[counter], scale, shift, 2, -1, black, mapper_image );
                
                Draw_Edges( mapper_graph[counter], scale, shift, 2, black, mapper_image );
            }
            
            imwrite( BSD_directory + image_name + "/" + image_name + "_Mapper.png", mapper_image );
            
            cout << "Completed mapper algorithm on " << image_name << "." << endl << endl;
        }
    }
    
    if (BSD)
    {
        clock_t start_time = clock();
        
        int test_directory_size = 0;
        int train_directory_size = 0;
        int val_directory_size = 0;
        string test_directory = BSD_directory + "BSR/BSDS500/data/images/test/";
        string train_directory = BSD_directory + "BSR/BSDS500/data/images/train/";
        string val_directory = BSD_directory + "BSR/BSDS500/data/images/val/";
        
        for (auto & p : boost::filesystem::directory_iterator( test_directory ))
        {
            ++test_directory_size;
        }
        
        for (auto & p : boost::filesystem::directory_iterator( train_directory ))
        {
            ++train_directory_size;
        }
        
        for (auto & p : boost::filesystem::directory_iterator( val_directory ))
        {
            ++val_directory_size;
        }
        
        int directory_size = test_directory_size + train_directory_size + val_directory_size;
        int iterations = directory_size;
        int skip = 0;
        double hopes_rms_error = 0, aR_rms_error = 0, mapper_rms_error = 0;
        string image_file;
        
        for (int counter_1 = 0; counter_1 < iterations; ++counter_1)
        {
            if (!BSD_File( counter_1, test_directory, test_directory_size, train_directory, train_directory_size, val_directory, val_directory_size, image_file ))
            {
                ++skip;
                continue;
            }
            
            Mat input_image;
             
            input_image = imread( image_file );
            
            vector<P2> cloud;
            vector<vector<Data_Pt>> clouds;
             
            Read_Cloud_From_Image( input_image, cloud, clouds );
            
            if (hopes_on_image)
            {
                vector<Graph> hopes_graph( clouds.size() );
                
                for (int counter = 0; counter < clouds.size(); ++counter)
                {
                    vector<P2> converted_cloud;
                    
                    Convert_Cloud_1( clouds[counter], converted_cloud );
                    
                    double max_birth = 0, min_death = 1e10;
                    Graph_H g;
                    
                    Hopes( converted_cloud, g, max_birth, min_death );
                    
                    Simplify_Graph( g, hopes_simp_type_2, min_death, mcsf, hopes_graph[counter] );
                }
                
                Graph hopes;
                
                Combine_Comps( hopes_graph, hopes );
                
                hopes_rms_error += Geometric_Approximation_Error( hopes, cloud ).second;
            }
            
            if (alphaReeb_on_image)
            {
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
                    
                    AlphaReeb_Parameters parameters( 4, 0 );
                    
                    AlphaReeb_Algorithm( nbhd_graph, parameters, alphaReeb_graph[counter] );
                }
                
                Graph alphaReeb;
                
                Combine_Comps( alphaReeb_graph, alphaReeb );
                
                aR_rms_error += Geometric_Approximation_Error( alphaReeb, cloud ).second;
            }
            
            if (mapper_on_image)
            {
                vector<Graph> mapper_graph( clouds.size() );
                
                for (int counter = 0; counter < clouds.size(); ++counter)
                {
                    Mapper_Parameters parameters( 15, 0.5, "Distance", 0.1, 3, 0 );
                    
                    Mapper( clouds[counter], parameters, mapper_graph[counter] );
                }
                
                Graph mapper;
                
                Combine_Comps( mapper_graph, mapper );
                
                mapper_rms_error += Geometric_Approximation_Error( mapper, cloud ).second;
            }
            
            cout << "Completed iteration " << counter_1 + 1 - skip << "." << endl;
        }
        
        hopes_rms_error = hopes_rms_error / (double)(iterations - skip);
        aR_rms_error = aR_rms_error / (double)(iterations - skip);
        mapper_rms_error = mapper_rms_error / (double)(iterations - skip);
        
        cout << endl;
        cout << hopes_rms_error << endl;
        cout << aR_rms_error << endl;
        cout << mapper_rms_error << endl << endl;
        
        ofstream ofs( BSD_directory + "Results/Results.txt" );
        
        ofs << "The RMS error of the three algorithms over " << iterations - skip << " images from the BSDS500 database:" << endl << endl;
        ofs << "Mapper: " << mapper_rms_error << "." << endl;
        ofs << "Alpha-Reeb: " << aR_rms_error << "." << endl;
        ofs << "HoPeS: " << hopes_rms_error << "." << endl;
        
        ofs.close();
        
        clock_t end_time = clock();
        
        cout << "Duration: " << (end_time - start_time) / (double)CLOCKS_PER_SEC << "s." << endl << endl;
    }
    
    return 0;
}
