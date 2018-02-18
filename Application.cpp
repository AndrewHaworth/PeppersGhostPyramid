#include<opencv2\opencv.hpp>

using namespace cv;

int main() {
	VideoCapture cap;
	if (!cap.open(0))
		return 0;
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
		frame90.copyTo(res(Rect(frame90.rows*2, frame90.cols, frame90.cols, frame90.rows)));
		frame180.copyTo(res(Rect(frame180.cols, frame180.rows*2, frame180.cols, frame180.rows)));
		frame270.copyTo(res(Rect(0, frame270.cols, frame270.cols, frame270.rows)));
		//namedWindow("Hypercam", WINDOW_NORMAL);
		namedWindow("Hypercam", CV_WINDOW_KEEPRATIO);
		//setWindowProperty("Hypercam", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);

		imshow("Hypercam", res);
		if (waitKey(10) == 27)
			break;
	}
	return(0);
}