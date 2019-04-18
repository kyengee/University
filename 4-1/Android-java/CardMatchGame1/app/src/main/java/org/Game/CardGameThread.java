package org.Game;

public class CardGameThread extends Thread {

	CardGameView m_View = null;
	
	CardGameThread(CardGameView _View){
		m_View = _View;
	}
	
	public void run(){
		while(true){
		//while(m_View != null ){
			// 吏�냽�곸쑝濡�移대뱶瑜�鍮꾧탳�댁���
			m_View.checkMatch();
		}
	}
	
}
