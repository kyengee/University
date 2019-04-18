package org.Game;

import java.util.Timer;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.os.CountDownTimer;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.util.TimeUtils;
import android.view.Display;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;


public class CardGameView extends View {

	public static final int STATE_READY =0 ; // 게임시작전 준비상태
	public static final int STATE_GAME=1 ; // 게임중
	public static final int STATE_END =2 ; // 게임종료

	// 게임의 상태값을 가질멤버변수
	private int m_state = STATE_READY; // 초기값은 준비상태


	private Bitmap m_BackGroundImage; // 배경이미지
	private Bitmap m_Card_Backside; // 카드뒷면

	// 카드 앞면 이미지 색상별로
	private Bitmap m_Card_Red;
	private Bitmap m_Card_Blue;
	private Bitmap m_Card_Green;

	// 화면에 표시될 카드들
	private Card m_Shuffle[][];

	// 짝맞추기 비교를 위한 변수
	private Card m_SelectCard_1 = null; // 첫번째로 선택한 카드
	private Card m_SelectCard_2 = null; // 두번째로 선택한 카드
	private boolean isReady = false;

	public CardGameView(Context context) {
		super(context);

		// 이미지들 불러오기
		m_BackGroundImage = BitmapFactory.decodeResource(getResources(), R.drawable.background,null);
		m_Card_Backside = BitmapFactory.decodeResource(getResources(), R.drawable.backside,null);
		m_Card_Red = BitmapFactory.decodeResource(getResources(),R.drawable.front_red);
		m_Card_Blue = BitmapFactory.decodeResource(getResources(),R.drawable.front_blue);
		m_Card_Green = BitmapFactory.decodeResource(getResources(),R.drawable.front_green);

		// 화면의 표시될 카드들만큼 할당받음 (2 x 3)
		m_Shuffle = new Card[3][2];

		// 카드들을 섞음
		SetCardShuffle();

		// 짝맞추기를 검사하는 스레드실행
		CardGameThread _thread = new CardGameThread(this);
		_thread.start();
	}

	@Override
	public void onDraw(Canvas canvas) {
		// 배경이미지 그려주기
		canvas.drawBitmap(m_BackGroundImage, 0,0,null);

		// 카드들을 그려주기
		for(int y = 0 ; y< 2; y++){
			for(int x =0 ; x<3;x++)
				// 카드의 앞면을 그려줘야하는경우
				if(m_Shuffle[x][y].m_state == Card.CARD_SHOW ||
						m_Shuffle[x][y].m_state == Card.CARD_PLAYEROPEN ||
						m_Shuffle[x][y].m_state == Card.CARD_MATCHED ){
					// 가지고 있는 색상값에 따라 다른 이미지 그려주기
					if(m_Shuffle[x][y].m_Color == Card.IMG_RED)
						canvas.drawBitmap(m_Card_Red, 35 + x*90, 150 + y*130,null);
					else if(m_Shuffle[x][y].m_Color == Card.IMG_GREEN)
						canvas.drawBitmap(m_Card_Green, 35 + x*90, 150 + y*130,null);
					else if(m_Shuffle[x][y].m_Color == Card.IMG_BLUE)
						canvas.drawBitmap(m_Card_Blue, 35 + x*90, 150 + y*130,null);
				}
				// 카드의 뒷면을 그려주어야하는경우
				else
					canvas.drawBitmap(m_Card_Backside, 35 + x*90, 150 + y*130,null);
		}
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {

		// 게임 준비중
		if(m_state == STATE_READY){
			startGame(); // 게임을 시작해준다.
			m_state = STATE_GAME;
		}
		// 게임중
		else if(m_state == STATE_GAME){
			// 비교할려고 두개의 카드를 이미 뒤집은경우
			if(m_SelectCard_1 != null && m_SelectCard_2 !=null)
				return true;
			int px = (int)event.getX();
			int py = (int)event.getY();
			for(int y = 0 ; y< 2; y++){
				for(int x =0 ; x<3;x++){
					// 각각카드들의 박스값을 생성
					Rect box_card = new Rect(35+x*90,150+y*130,35+x*90 + 80,150 + y*130+115);
					if(box_card.contains(px,py)) { // (x , y) 에 위치한  카드가 선택되었다.
						if(m_Shuffle[x][y].m_state != Card.CARD_MATCHED) // 맞춘카드는 뒤집을필요가없다.
							if(m_SelectCard_1 == null){ // 첫 카드를 뒤집으려는것이라면
								m_SelectCard_1 = m_Shuffle[x][y];
								m_SelectCard_1.m_state = Card.CARD_PLAYEROPEN;
							}
							else{ // 이미 첫번째 카드가 뒤집혀있으니 두번째로 뒤집으려는거라면
								if(m_SelectCard_1 != m_Shuffle[x][y]){ // 중복뒤집기방지
									isReady = false;
									Log.i("OnTouch", "1-step1");
									m_SelectCard_2 = m_Shuffle[x][y];
									Log.i("OnTouch", "1-step2");
									m_SelectCard_2.m_state = Card.CARD_PLAYEROPEN;
									Log.i("OnTouch", "1-step3");
									isReady = true;
								}
							}
					}
				}
			}

		}
		// 게임완료
		else if(m_state == STATE_END){
			// 게임준비상태로 변경
			m_state = STATE_READY;
		}

		// 화면을갱신해준다.
		invalidate();
		return true;
	}

	public void startGame(){
		// 모든 카드들을 뒷면 상태로 만들어 준다.
		m_Shuffle[0][0].m_state = Card.CARD_CLOSE;
		m_Shuffle[0][1].m_state = Card.CARD_CLOSE;
		m_Shuffle[1][0].m_state = Card.CARD_CLOSE;
		m_Shuffle[1][1].m_state = Card.CARD_CLOSE;
		m_Shuffle[2][0].m_state = Card.CARD_CLOSE;
		m_Shuffle[2][1].m_state = Card.CARD_CLOSE;

		// 화면을갱신해준다.
		invalidate();
	}

	public void SetCardShuffle(){
		// 각각의 색을 가진 카드들을 생성
		m_Shuffle[0][0]= new Card(Card.IMG_RED);
		m_Shuffle[0][1]= new Card(Card.IMG_BLUE);
		m_Shuffle[1][0]= new Card(Card.IMG_GREEN);
		m_Shuffle[1][1]= new Card(Card.IMG_GREEN);
		m_Shuffle[2][0]= new Card(Card.IMG_BLUE);
		m_Shuffle[2][1]= new Card(Card.IMG_RED);

	}

	public void checkMatch(){
		// 두 카드중 하나라도 선택이않되었다면 비교해줄 필요가없다.
		if(m_SelectCard_1 == null || m_SelectCard_2 == null || !isReady )
			return;
		// 두카드의 색상을 비교한다.
		if(m_SelectCard_1.m_Color == m_SelectCard_2.m_Color){
			// 두 카드의 색상이 같은경우 두카드를 맞추어진상태로 바꾸어준다
			m_SelectCard_1.m_state = Card.CARD_MATCHED;
			m_SelectCard_2.m_state = Card.CARD_MATCHED;
			// 다시 선택을 할수있게 null값을 넣어준다.
			Log.i("CardMatch", "2-step1");
			m_SelectCard_1 = null;
			Log.i("CardMatch", "2-step2");
			m_SelectCard_2 = null;
			Log.i("CardMatch", "2-step3");
		}
		else{
			// 두 카드의 색상이 다른경우 대기시간을 주어 결과를 확인하게한다.
			try {
				Thread.sleep(500);
			} catch (InterruptedException e) {
			}

			// 두카드를 이전처럼 뒷면으로 돌려준다.
			m_SelectCard_1.m_state = Card.CARD_CLOSE;
			m_SelectCard_2.m_state = Card.CARD_CLOSE;

			// 다시 선택을 할수있게 null값을 넣어준다.
			Log.i("CardMatch", "3-step4");
			m_SelectCard_1 = null;
			Log.i("CardMatch", "3-step5");
			m_SelectCard_2 = null;
			Log.i("CardMatch", "3-step6");

		}

		// 화면을 갱신해준다.
		//invalidate(); // 스레드에서 사용하므로
		postInvalidate();
	}

}
