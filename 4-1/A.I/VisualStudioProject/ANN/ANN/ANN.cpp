// ANN.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include "opencv2/opencv.hpp"

#define TRAININGDATA 500
#define TESTDATA 10000
#define IMAGESIZE 900

void labelData(cv::Mat& data, cv::Mat classes) {
	for (int i = 0; i < data.rows; i++) {
		float x = data.at<float>(i, 0);
		float y = data.at<float>(i, 0);

		if ((x < 0.5 && y < 0.5) || (x > 0.5 && y > 0.5))
			classes.at<float>(i, 0) = -1;
		else
			classes.at<float>(i, 0) = 1;
	}
}

void ANN(cv::Mat& trainData, cv::Mat& trainClasses, cv::Mat& testData, cv::Mat& testClasses) {

	cv::Mat layer = cv::Mat(3, 1, CV_32SC1);

	layer.row(0) = cv::Scalar(2);
	layer.row(1) = cv::Scalar(10);
	layer.row(2) = cv::Scalar(1);

	CvANN_MLP ann;
	CvANN_MLP_TrainParams param;
	CvTermCriteria criteria;
	criteria.max_iter = 500;
	criteria.epsilon = 0.00001f;
	criteria.type = CV_TERMCRIT_ITER | CV_TERMCRIT_EPS;

	param.train_method = CvANN_MLP_TrainParams::BACKPROP;
	param.bp_dw_scale = 0.1f;
	param.bp_moment_scale = 0.1f;
	param.term_crit = criteria;
	ann.create(layer);

	ann.train(trainData, trainClasses, cv::Mat(), cv::Mat(), param);

	cv::Mat dstImage = cv::Mat::zeros(cv::Size(IMAGESIZE, IMAGESIZE), CV_8UC3);

	cv::Mat output = cv::Mat(1, 1, CV_32FC1);

	for (int i = 0; i < testData.rows; i++) {
		cv::Mat temp = testData.row(i);

		ann.predict(temp, output);

		int x = temp.at<float>(0, 0) * IMAGESIZE;
		int y = temp.at<float>(0, 1) * IMAGESIZE;

		if (output.at<float>(0, 0) < 0)
			cv::circle(dstImage, cv::Point(x, y), 2, cv::Scalar(0, 255, 0));
		else
			cv::circle(dstImage, cv::Point(x, y), 2, cv::Scalar(0, 0, 255));
	}

	cv::imshow("dstimage", dstImage);
	cv::waitKey(0);

}

void main()
{
	cv::Mat trainData = cv::Mat(TRAININGDATA, 2, CV_32FC1);
	cv::Mat testData = cv::Mat(TESTDATA, 2, CV_32FC1);

	cv::randu(trainData, 0, 1);
	cv::randu(testData, 0, 1);

	cv::Mat trainClasses = cv::Mat(trainData.rows, 1, CV_32FC1);
	cv::Mat testClasses = cv::Mat(testData.rows, 1, CV_32FC1);

	labelData(trainData, trainClasses);
	ANN(trainData, trainClasses, testData, testClasses);
}


// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
