#pragma once

#include "Single_Edge_Clustering.h"
#include "Convert_Cloud.h"

void CannyDetector ( Mat const& InputImage, int LowThreshold, double ratio, Mat& CannyEdges )
{
    int SizeKernel = 3;
    Mat EdgesImage;
    blur( InputImage, EdgesImage, Size( 3, 3 ) );
    Canny( EdgesImage, CannyEdges, LowThreshold, ratio * LowThreshold, SizeKernel );
}

void LoadCloud ( Mat const& ImageCloud, vector<P2>& cloud )
{
    for (int j = 0; j < ImageCloud.rows; ++j)
    {
        for (int i = 0; i < ImageCloud.cols; ++i)
        {
            if (ImageCloud.at<uchar>( j, i ) != 0) cloud.push_back( P2( i, j ) );
        }
    }
}

void Read_Cloud_From_Image ( string const& image_directory, string const& image_name, vector<vector<Data_Pt>>& clouds )
{
    Mat InputImage;
    
    InputImage = imread( image_directory + image_name + ".jpg" );
    
    int CannyLowThreshold = 75;
    double CannyRatio = 3;
    Mat CannyEdges;
    
    CannyDetector( InputImage, CannyLowThreshold, CannyRatio, CannyEdges);
    
    imwrite( image_directory + "Canny_" + image_name + ".png", CannyEdges );
    
    vector<P2> cloud;
    
    LoadCloud( CannyEdges, cloud );
    
    vector<vector<P2>> P2_clouds;
    P2_clouds.assign( 1, cloud );
    
    Single_Edge_Clustering( 3, P2_clouds );
    
    clouds.resize( P2_clouds.size() );
    
    for (int counter = 0; counter < P2_clouds.size(); ++counter)
    {
        Convert_Cloud_2( P2_clouds[counter], clouds[counter] );
    }
}
