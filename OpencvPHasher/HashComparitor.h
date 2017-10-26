#pragma once

#include "opencv2/core.hpp"
#include "opencv2/core/ocl.hpp"
#include "opencv2/img_hash.hpp"

using namespace std;
using namespace cv::img_hash;


template <typename T>
class HashComparitor {

public:
	void compareHashes(Mat hash1, Mat hash2, double *result);
	void compare(const Mat &hash1, const Mat &image, double *result);
	void retrieveHashFromMatImage(const Mat &image, Mat *output);
	void compareImages(const Mat &a, const Mat &b);

	HashComparitor();
	~HashComparitor();

private:
	Ptr<ImgHashBase> func;
};

template<typename T>
inline void HashComparitor<T>::compareHashes(Mat hash1, Mat hash2, double *result) 
{
	*result = func->compare(hash1, hash2);

	/*
	cout << "hash A Type: " << hash1.type() << endl;
	cout << "hash A: " << hash1 << endl;
	cout << "hash A col size: " << hash1.cols << endl;
	cout << "hash A row size: " << hash1.rows << endl;

	cout << "hash B Type: " << hash2.type() << endl;
	cout << "hash B: " << hash2 << endl;
	cout << "hash B col size: " << hash2.cols << endl;
	cout << "hash B row size: " << hash2.rows << endl;
	cout << "hash B step: " << hash2.step << endl;
	*/
}

template<typename T>
inline void HashComparitor<T>::compare(const Mat & hash1, const Mat & image, double *result)
{
	Mat hash2;
	func->compute(image, hash2);

	*result = func->compare(hash1, hash2); //the lower the value for PHash the more similar
											 //double res = (1 - v) / 64.0;
	/*
	cout << "hash A Type: " << hash1.type() << endl;
	cout << "hash A: " << hash1 << endl;
	cout << "hash A col size: " << hash1.cols << endl;
	cout << "hash A row size: " << hash1.rows << endl;
	cout << "hash A step: " << hash1.step << endl;

	cout << "hash B Type: " << hash2.type() << endl;
	cout << "hash B: " << hash2 << endl;
	cout << "hash B col size: " << hash2.cols << endl;
	cout << "hash B row size: " << hash2.rows << endl;
	cout << "hash B step: " << hash2.step << endl;
	*/
	//cout << "compare: " << *result << endl;

}

template <typename T>
inline void HashComparitor<T>::compareImages(const Mat &a, const Mat &b) {
	Mat hash1;
	Mat hash2;
	func->compute(a, hash1);
	func->compute(b, hash2);

	cout << "compare: " << func->compare(hash1, hash2) << endl;
}

template<typename T>
inline void HashComparitor<T>::retrieveHashFromMatImage(const Mat & image, Mat *output)
{
	func->compute(image, *output);
	//cout << "computed hash" << *output << endl;
}

template<typename T>
inline HashComparitor<T>::HashComparitor()
{
	ocl::setUseOpenCL(false);
	func = T::create();
}

template<typename T>
inline HashComparitor<T>::~HashComparitor()
{
}
