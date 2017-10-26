#include "stdafx.h"
#include "Subject.h"


void Subject::setImage(void *buf, int h, int w)
{
	image = Mat(h, w, CV_8UC3, Scalar(0, 0, 0));
	image.data = (uchar *)buf;
}

Mat& Subject::getImage()
{
	return image;
}

Mat* Subject::getHash() {
	return &hash;
}

void Subject::setHash(const Mat &h)
{
	hash = h;
}

void Subject::setKeypoints(vector<cv::KeyPoint> kp)
{
	keypoints = kp;
}

void Subject::setDescriptorsFromFloatBuffer(float *descs, int rows, int cols, int matType)
{
	descriptors = cv::Mat(rows, cols, matType, descs);
}


void Subject::addToKeyPoints(float x, float y) {
	cv::KeyPoint kp;
	cv::Point2f p;
	p.x = x;
	p.y = y;
	kp.pt = p;
	//keypointsA.push_back(kp);
}


Mat Subject::getDescriptors()
{
	return descriptors;
}

vector<cv::KeyPoint> Subject::getKeypoints()
{
	return keypoints;
}

void Subject::printDescriptors() {
	cout << descriptors << endl;
}

void Subject::checkSubjectKeypoints() {
	cout << "Subject Keypoints: " << keypoints.size() << endl;
	cout << "Subject Descriptors: " << descriptors.size() << endl;
}

void Subject::cleanUp()
{
	keypoints.clear();
	descriptors.release();
	image.release();
}

Subject::Subject()
{
}


Subject::~Subject()
{
}
