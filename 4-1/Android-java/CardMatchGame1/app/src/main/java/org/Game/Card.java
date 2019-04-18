package org.Game;

public class Card {

	// 카드의 상태들
	public static final int CARD_SHOW = 0; // 게임시작전보여주는상태
	public static final int CARD_CLOSE = 1; // 게임시작후 뒤집힌 상태
	public static final int CARD_PLAYEROPEN = 2; // 플레이어의 선택으로 열린상태
	public static final int CARD_MATCHED = 3; // 짝이 맞춰져 열린상태
	
	// 카드의 색상
	public static final int IMG_RED =1 ; // 빨간
	public static final int IMG_GREEN =2 ; // 초록
	public static final int IMG_BLUE =3 ; // 파랑


	
	public int m_state; // 상태값
	public int m_Color; // 색상값
	
	
	public Card(int _Color){
		m_state = CARD_SHOW;
		m_Color = _Color;
	}

}
