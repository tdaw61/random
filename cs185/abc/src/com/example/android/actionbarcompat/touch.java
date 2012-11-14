package com.example.android.actionbarcompat;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.graphics.PointF;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;
import android.view.ScaleGestureDetector.OnScaleGestureListener;
import android.widget.ImageView;
import android.support.v4.view.*;

public class touch extends ImageView implements OnScaleGestureListener {

	double oldAngle;
	boolean rotate;
	float width, height, sw, sh;
	double ang;
	ScaleGestureDetector myScaleGD;
	Matrix myMatrix;
	PointF p1, p2, mid;

	public touch(Context context, Bitmap bitmap) {
		super(context);
		super.setImageBitmap(bitmap);
		setImageMatrix(new Matrix());
		setScaleType(ScaleType.MATRIX);
		myScaleGD = new ScaleGestureDetector(context, this);
		height = bitmap.getHeight();
		width = bitmap.getWidth();
		p1 = new PointF();
		p2 = new PointF();
		mid = new PointF();
		rotate = false;

	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {

		switch (event.getAction()) {
		case MotionEvent.ACTION_POINTER_DOWN:
			rotate = false;

			p2.set(event.getX(), event.getY());
			break;
		case MotionEvent.ACTION_DOWN:
			rotate = false;
			p1.set(event.getX(), event.getY());
			break;
		case MotionEvent.ACTION_MOVE:
			if (event.getPointerCount() == 1) {
				rotate = false;
				myMatrix.postTranslate(event.getX() - p1.x, event.getY() - p1.y);
				p1.set(event.getX(), event.getY());
				break;
			} else if (event.getPointerCount() == 2) {
				p1.set(event.getX(), event.getY());
				p2.set(event.getX(1), event.getY(1));
				mid.set((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
				if (rotate == true)
					myMatrix.postRotate(
							(float) ((180 / Math.PI)
									* Math.atan2(p2.y - p1.y, p2.x - p1.x) - oldAngle),mid.x, mid.y);
				else
					rotate = !rotate;
				oldAngle = (180 / Math.PI)
						* Math.atan2(p2.y - p1.y, p2.x - p1.x);
			}
		}
		myScaleGD.onTouchEvent(event);
		invalidate();
		return true;
	}



	@Override
	public void setImageBitmap(Bitmap bm) {
		super.setImageBitmap(bm);
		height = bm.getHeight();
		width = bm.getWidth();
	}
	@Override
	public void setImageMatrix(Matrix matrix) {
		myMatrix = matrix;
		super.setImageMatrix(matrix);
	}
	
	@Override
	protected void onDraw(Canvas canvas) {
		setImageMatrix(myMatrix);
		super.onDraw(canvas);
	}

	@Override
	protected void onSizeChanged(int w, int h, int oldw, int oldh) {
		sw = w;
		sh = h;
		float ratio;
		if (sw / width < sh / height)
			ratio = sw / width;
		else
			ratio = sh / height;
		myMatrix.preScale(ratio, ratio);
		myMatrix.postTranslate(sw / 2 - (ratio * width) / 2, (sh / 2)
				- (ratio * height) / 2);
		invalidate();
		super.onSizeChanged(w, h, oldw, oldh);
	}
	
	public boolean onScale(ScaleGestureDetector detector) {
		myMatrix.postScale(detector.getScaleFactor(),
				detector.getScaleFactor(), detector.getFocusX(),
				detector.getFocusY());
		return true;
	}



	public boolean onScaleBegin(ScaleGestureDetector detector) {
		return true;
	}

	public void onScaleEnd(ScaleGestureDetector detector) {
		// not used
	}

}
