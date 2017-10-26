#pragma once

class Subject
{
public:
	void setImage(void *buf, int h, int w);
	Mat& getImage();

	Mat* getHash();

	void setHash(const Mat &h);
	void setKeypoints(vector<cv::KeyPoint> kp);
	void setDescriptorsFromFloatBuffer(float *kpts, int rows, int cols, int matType);
	void addToKeyPoints(float x, float y);
	Mat getDescriptors();
	vector<cv::KeyPoint> getKeypoints();
	void printDescriptors();
	void checkSubjectKeypoints();

	void cleanUp();
	Subject();
	~Subject();

private:
	Mat image;
	Mat hash;
	vector<cv::KeyPoint> keypoints;
	Mat descriptors;

};