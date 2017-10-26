#include "stdafx.h"
#include "FeatureExtractor.h"

void FeatureExtractor::setImage(void * buf, int height, int width)
{
	image = Mat(height, width, CV_8UC3, Scalar(0, 0, 0));
	image.data = (uchar *)buf;
}

Mat& FeatureExtractor::getImage()
{
	return image;
}

void FeatureExtractor::setKeypointsAndDescriptors(cv::Ptr<FeatureDetector> detector)
{
	detector->detectAndCompute(image, noArray(), keyPoints, descriptors);
}

void FeatureExtractor::getDescriptorsAsString(char *)
{
}


/* Don't use in production. You don't have a way of freeing what's returned here */
char * FeatureExtractor::getDescriptorsAsString()
{
	cout << "rows: " << descriptors.rows << endl;
	cout << "cols: " << descriptors.cols << endl;
	cout << "type: " << descriptors.type() << endl;
	std::string com = "";
	std::string text = "";
	char* descAsChar;

	for (int i = 0; i < descriptors.rows; i++) {
		for (int j = 0; j<descriptors.cols; j++) {
			//text += com + std::to_string(descriptorsA.at<float>(i, j)); //losing precision
			//ostringstream is one of the slower types of conversion. Boost library has some options
			std::ostringstream out; 
			out << (descriptors.ptr<float>(i))[j];
			text += com + out.str();
			out.clear();
			com = ",";
		}
	}
	descAsChar = new char[text.size() + 1];
	std::copy(text.begin(), text.end(), descAsChar);
	descAsChar[text.size()] = '\0';
	return descAsChar;
}

void FeatureExtractor::getDescriptorsRows(int *r)
{
	*r = descriptors.rows;
}

void FeatureExtractor::getDescriptorsCols(int *c)
{
	*c = descriptors.cols;
}

void FeatureExtractor::getDescriptorsType(int * c)
{
	*c = descriptors.type();
}


void FeatureExtractor::getDescriptorsByReference(float **buf)
{
	int cols = descriptors.cols;
	for (int i = 0; i < descriptors.rows; i++) {
		for (int j = 0; j<descriptors.cols; j++) {
			//cout << "inserting at index: " << (i*cols) + j << " value: " << descriptors.at<float>(i, j) << endl;
			(*buf)[(i* cols) + j] = (descriptors.ptr<float>(i))[j];
		}
	}
}

/*
* in Java you will pass 'float[] p' to this function
*/
void FeatureExtractor::fillDescriptorArray(float * buf)
{
	int cols = descriptors.cols;
	for (int i = 0; i < descriptors.rows; i++) {
		for (int j = 0; j<descriptors.cols; j++) {
			buf[(i* cols) + j] = (descriptors.ptr<float>(i))[j]; //descriptors.at<float>(i, j);
		}
	}
}

void FeatureExtractor::printDescriptors()
{
	ofstream outfile("C:\\output\\dll_subjectDescriptors.txt", ios::out | std::ofstream::binary);
	std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
	std::cout.rdbuf(outfile.rdbuf()); //redirect std::cout to new.txt! 

	for (int i = 0; i < descriptors.rows; i++) {
		for (int j = 0; j<descriptors.cols; j++) {
			cout << (descriptors.ptr<float>(i))[j] << ",";
		}
	}
}

void FeatureExtractor::cleanup()
{
	descriptors.release();
	image.release();
}

Mat& FeatureExtractor::getDescriptors()
{
	return descriptors;
}

void FeatureExtractor::fillKeypointsArray(float * buf)
{
	for (int i = 0; i < keyPoints.size(); i+= 2) {
		//cout << keyPoints.at(i).pt.x << " " << keyPoints.at(i).pt.y << ",";
		buf[i] = keyPoints.at(i).pt.x;
		buf[i + 1] = keyPoints.at(i).pt.y;
	}
}

void FeatureExtractor::getKeypointsSize(int *r)
{
	*r = keyPoints.size();
}

vector<cv::KeyPoint> FeatureExtractor::getKeypoints()
{
	return keyPoints;
}

FeatureExtractor::FeatureExtractor()
{
}

FeatureExtractor::~FeatureExtractor()
{
}
