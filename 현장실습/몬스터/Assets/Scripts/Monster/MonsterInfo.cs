using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterInfo : MonoBehaviour
{
    
    private bool moveType;//true 이동 false 고정
    private bool firstAttack;//true 선공 false 비선공
    private float attackTime;//공격시간
    private float attackDistance;//사정거리
    private int hp;//최대체력
    private int power;//공격력
    private int defence;//방어력
    private float moveSpeed;//이동속도
    private string dropItem;//1,44,2,33,5,6~


    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void SetMonster(GameObject monster, GameObject monsterUI)//몬스터 정보 설정
    {
        int num = monster.GetComponent<Monster>().monsterNum;//몬스터 번호
        Monster mon = monster.GetComponent<Monster>();
        monster.GetComponent<Animator>().runtimeAnimatorController = Resources.Load("Monster/AnimationControllers/" + Convert.ToString(num) + "/" + Convert.ToString(num) + "Body") as RuntimeAnimatorController;//애니메니터 몬스터 번호에 맞춰서 설정
        
        monster.transform.parent.transform.Find("MonsterUI").transform.Find("Canvas").
            transform.Find("BackgroundBar").transform.Find("Name").GetComponent<SpriteRenderer>().
            sprite = (Sprite)Resources.Load("Monster/MonsterName/" + Convert.ToString(num) + "Name", typeof(Sprite));//애니메니터 이름 번호에 맞춰서 설정
        
        /*
        moveType;//true 이동 false 고정
        firstAttack;//true 선공 false 비선공
        attackTime;//공격시간
        attackDistance;//사정거리
        hp;//최대체력
        power;//공격력
        defence;//방어력
        moveSpeed;//이동속도
        dropItem;//1,44,2,33,5,6~
        */
        switch (num)
        {
            case 1://DarkSnake
                mon.moveType = true;
                mon.firstAttack = true;
                mon.attackTime = 3f;
                mon.attackDistance = 3f;
                mon.hp = 100;
                mon.power = 10;
                mon.defence = 10;
                mon.moveSpeed = 2;
                mon.dropItem = "1,4";
                break;
            case 2://DeserSnake
                mon.moveType = true;
                mon.firstAttack = false;
                mon.attackTime = 3f;
                mon.attackDistance = 3f;
                mon.hp = 50;
                mon.power = 20;
                mon.defence = 10;
                mon.moveSpeed = 2;
                mon.dropItem = "1,4";
                break;
        }
    }
}
