using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterAttackEffect : MonoBehaviour
{
    
    private GameObject player;
    public int monsterNum;//몬스터 번호

    // Start is called before the first frame update
    void Start()
    {
        player = GameObject.Find("Player");

        GetComponent<Animator>().runtimeAnimatorController = Resources.Load("Monster/AnimationControllers/" + Convert.ToString(monsterNum) + "/" + Convert.ToString(monsterNum) + "AttackEffect") as RuntimeAnimatorController;//애니메니터 몬스터 번호에 맞춰서 설정

        Vector3 pos = player.transform.position;
        pos.y -= 0.7f;
        transform.position = pos;

        ///나중에 함수로 바꿔야함
        GameObject damageUI = Instantiate(Resources.Load("UI/Prefabs/DamageUI")) as GameObject;//데미지UI 오브젝트생성
        damageUI.transform.parent = player.transform.parent.transform;//Player오브젝트 자식으로 설정
        damageUI.GetComponent<DamageUI>().gameObj = player.gameObject;//Player오브젝트
        damageUI.GetComponent<DamageUI>().checkPlayer = true;//플레이어,몬스터 체크 true = 플레이어, false = 몬스터
        damageUI.transform.Find("Canvas").transform.Find("Damage").GetComponent<Damage>().damage = 20;//30데미지
        damageUI.transform.Find("Canvas").transform.Find("Damage").GetComponent<Damage>().color = "#ffff00ff";

        //SetPos(monsterNum);//몬스터 번호에 따른 위치 설정
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 pos = player.transform.position;
        pos.y -= 0.7f;
        transform.position = pos;
        //SetPos(monsterNum);//몬스터 번호에 따른 위치 설정
    }

    private void SetPos(int num)//몬스터 번호에 따른 위치 설정
    {
        if (num == 0)//0(공격이펙트가 없음)
        {
            Destroy(gameObject);//오브젝트 삭제
            return;
        }
        Vector3 pos = player.transform.position;//플레이어 위치로 이동
        switch (num)//몬스터 번호에 따라 위치 설정
        {
            case 1:
                pos.x -= 0.7f;
                pos.y -= 0.7f;
                break;
            case 2:
                break;
        }
        transform.position = pos;
    }



    private void EndEffect()//이펙트 애니메이션 종료
    {
        Destroy(gameObject);//오브젝트 삭제
    }

}
