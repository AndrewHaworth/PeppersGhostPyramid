#include<opencv2\opencv.hpp>
#include"application.h"
#include<Windows.h>

void printMenu() {
	using namespace std;
	cout << "1. See Pepper's Ghost Pyramid Live\n"
		"2. See the edge detection feature\n"
		"3. See an animation within the pyramid\n"
		"4. Exit the Application" << endl;
}

void dupeVideo(cv::Mat &orig) {
	using namespace cv;

	Mat frame, frame90, frame180, frame270;
	orig(Rect(Point(150, 450), Point(450, 150))).copyTo(frame);
	//orig.copyTo(frame);
	rotate(frame, frame90, ROTATE_90_CLOCKWISE);
	rotate(frame, frame180, ROTATE_180);
	rotate(frame, frame270, ROTATE_90_COUNTERCLOCKWISE);

	Mat3b res(3 * frame.rows, 3 * frame.cols, Vec3b(0, 0, 0));
	frame.copyTo(res(Rect(frame.cols, 0, frame.cols, frame.rows)));
	frame90.copyTo(res(Rect(frame90.rows * 2, frame90.cols, frame90.cols, frame90.rows)));
	frame180.copyTo(res(Rect(frame180.cols, frame180.rows * 2, frame180.cols, frame180.rows)));
	frame270.copyTo(res(Rect(0, frame270.cols, frame270.cols, frame270.rows)));
	namedWindow("LiveCam", WINDOW_NORMAL);
	//namedWindow("LiveCam", WINDOW_GUI_EXPANDED);
	setWindowProperty("LiveCam", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);

	imshow("LiveCam", res);
}

void camShow() {
	using namespace cv;
	VideoCapture cap;
	if (!cap.open(0)) {
		MessageBox(nullptr, TEXT("No Webcam Detected!"),
			TEXT("Please connect a webcam and try again!"), MB_OK);
		return;
	}
	for (;;) {
		Mat orig;
		cap >> orig;
		dupeVideo(orig);
		if (waitKey(1) == 27) {
			destroyWindow("LiveCam");
			return;
		}
	}
}

void edges() {
	using namespace cv;
	VideoCapture cap;
	if (!cap.open(0)) {
		MessageBox(nullptr, TEXT("No Webcam Detected!"),
			TEXT("Please connect a webcam and try again!"), MB_OK);
		return;
	}
	for (;;) {
		Mat orig, out, blur, gray;
		cap >> orig;
		cvtColor(orig, gray, CV_BGR2GRAY);
		GaussianBlur(gray, blur, Size(5, 5), 2);
		Canny(blur, out, 45, 90);
		dupeVideo(out);
		if (waitKey(1) == 27) {
			destroyWindow("LiveCam");
			return;

		}
	}
}

void menu() {
	using namespace std;
	int a;
	cout << "Welcome to Pepper's Ghost Pyramid!" << endl;
	for (;;) {
		cout << "What would you like to do?" << endl;
		printMenu();
		cin >> a;
		switch (a) {
		case 1:
			camShow();
			break;
		case 2:
			edges();
			break;
		case 3:
			cout << "Should animate" << endl;
			break;
		case 4:
			return;
			break;
		default:
			cout << "Not a valid command!" << endl;
			break;
		}
		//cv::destroyAllWindows();
	}
	cout << "Thank you!" << endl;
}

int main() {
	menu();
	return(0);
}
