#pragma once

using namespace std;
using namespace cv;

class FeatureExtractor
{

public:

	void setImage(void *buf, int height, int width);
	cv::Mat& getImage();
	void setKeypointsAndDescriptors(cv::Ptr<FeatureDetector> detector);
	void getDescriptorsAsString(char *);
	char *getDescriptorsAsString();
	void getDescriptorsRows(int *r);
	void getDescriptorsCols(int *c);
	void getDescriptorsType(int *c);
	void getDescriptorsByReference(float **buf);
	void fillDescriptorArray(float *buf);
	void printDescriptors();
	void cleanup();
	Mat& getDescriptors();

	void fillKeypointsArray(float *buf);
	void getKeypointsSize(int * r);
	vector<cv::KeyPoint> getKeypoints();

	FeatureExtractor();
	~FeatureExtractor();

private:
	cv::Mat image;
	Mat descriptors;
	vector<cv::KeyPoint> keyPoints;


};