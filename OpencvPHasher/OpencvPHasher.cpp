// OpencvPHasher.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"


extern "C" {

	FeatureExtractor fe;
	HashComparitor<PHash> hc;
	Subject subject;

	DECLDIR void setSubjectImage(void *buf, int h, int w) {
		subject.setImage(buf, h, w);
		hc.retrieveHashFromMatImage(subject.getImage(), subject.getHash());
		//cout << "subject image hash " << subject.getHash() << endl;
	}


	/*
	* Functions to set the Scene (where we are looking for the subject)
	*/
	DECLDIR void setSceneImage(void *buf, int h, int w) {
		fe.setImage(buf, h, w);
	}

	/* Functions to compare hashes */
	DECLDIR void HashAndCompare(void *buf1, int h1, int w1, double *compareResult) {
		fe.setImage(buf1, h1, w1);
		hc.compare(*subject.getHash(), fe.getImage(), compareResult);
		//test_one<PHash>("PHash", subject.getImage(), fe.getImage());
	}

	/*Function to compare two previously computed hashes stored in the DB */
	DECLDIR void comparePrecomputedHashes(int* hash1, int* hash2, double *result) {
		vector<uchar> hv1, hv2;

		//Mat expects unsigned char. 
		//gotta be a more efficient way than this
		for (int i = 0; i < 8; i++) {
			hv1.push_back((uchar)hash1[i]);
			hv2.push_back((uchar)hash2[i]);
		}

		Mat h1 = cv::Mat(1, 8, 0, hv1.data());
		Mat h2 = cv::Mat(1, 8, 0, hv2.data());

		hc.compareHashes(h1, h2, result);
	}

	/* Testing Function for comparing hashes of two images */
	DECLDIR void CompareImageHash(void *buf1, int h1, int w1, void *buf2, int h2, int w2) {
		FeatureExtractor im1;
		im1.setImage(buf1, h1, w1);

		FeatureExtractor im2;
		im2.setImage(buf2, h2, w2);

		hc.compareImages(im1.getImage(), im2.getImage());
		//test_one<PHash>("PHash", im1.getImage(), im2.getImage());
	}

}