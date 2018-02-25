#include<opencv2\opencv.hpp>
#include"application.h"

void printMenu() {
	using namespace std;
	cout << "1. See Pepper's Ghost Pyramid Live\n"
		"2. See an animation within the pyramid\n"
		"3. Exit the Application" << endl;
}

void camShow() {
	using namespace cv;
	VideoCapture cap;
	if (!cap.open(0))
		return;
	for (;;) {
		Mat orig, frame, frame90, frame180, frame270;
		cap >> orig;
		orig(Rect(Point(150, 450), Point(450, 150))).copyTo(frame);
		//orig.copyTo(frame);
		rotate(frame, frame90, ROTATE_90_CLOCKWISE);
		rotate(frame, frame180, ROTATE_180);
		rotate(frame, frame270, ROTATE_90_COUNTERCLOCKWISE);
		if (frame.empty())
			break;

		Mat3b res(3 * frame.rows, 3 * frame.cols, Vec3b(0, 0, 0));
		frame.copyTo(res(Rect(frame.cols, 0, frame.cols, frame.rows)));
		frame90.copyTo(res(Rect(frame90.rows * 2, frame90.cols, frame90.cols, frame90.rows)));
		frame180.copyTo(res(Rect(frame180.cols, frame180.rows * 2, frame180.cols, frame180.rows)));
		frame270.copyTo(res(Rect(0, frame270.cols, frame270.cols, frame270.rows)));
		namedWindow("Peppercam", WINDOW_NORMAL);
		//namedWindow("Peppercam", WINDOW_GUI_EXPANDED);
		setWindowProperty("Peppercam", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);

		imshow("Peppercam", res);
		if (waitKey(1) == 27) {
			destroyWindow("Peppercam");
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
			cout << "Should animate" << endl;
			break;
		case 3:
			return;
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



