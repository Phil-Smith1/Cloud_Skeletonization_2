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

void Read_Cloud_From_Image ( string const& image_directory, string const& image_name, Mat const& InputImage, vector<vector<Data_Pt>>& clouds )
{
    int CannyLowThreshold = 75;
    double CannyRatio = 3;
    Mat CannyEdges;
    
    CannyDetector( InputImage, CannyLowThreshold, CannyRatio, CannyEdges);
    
    Mat dst;
    
    CannyEdges.copyTo( dst );
    
    cvtColor( dst, dst, COLOR_GRAY2BGR );
    
    for (int y = 0; y < dst.rows; ++y)
    {
        for (int x = 0; x < dst.cols; ++x)
        {
            if (dst.at<Vec3b>( Point( x,y ) )[0] > 10)
            {
                dst.at<Vec3b>( Point( x,y ) )[0] = dst.at<Vec3b>( Point( x,y ) )[1] = 0;
            }
            
            else dst.at<Vec3b>( Point( x,y ) )[0] = dst.at<Vec3b>( Point( x,y ) )[1] = dst.at<Vec3b>( Point( x,y ) )[2] = 255;
        }
    }
    
    for (int y = 0; y < dst.rows; ++y)
    {
        for (int x = 0; x < dst.cols; ++x)
        {
            if (dst.at<Vec3b>( Point( x,y ) )[0] > 10)
            {
                dst.at<Vec3b>( Point( x,y ) ) = InputImage.at<Vec3b>( Point( x, y ) );
            }
        }
    }
    
    //addWeighted( InputImage, 0.5, dst, 0.5, 0, dst );
    
    imwrite( image_directory + "Canny_" + image_name + ".png", dst );
    
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
