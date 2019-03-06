using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class MonsterManager : MonoBehaviour
{
    
    [SerializeField]
    private int monsterNum;//몬스터 번호
    [SerializeField]
    private bool monsterBoss;//몬스터 보스 true 보스 false 일반몬스터
    [SerializeField]
    private int monsterCount;//몬스터 생성 숫자
    [SerializeField]
    private string[] monsterPos;//몬스터 생성 위치[x y](float)(가운데 ' ')
    [SerializeField]
    private float responseTime;//부활시간 0이면 부활x

    private GameObject[] mon;//몬스터 프리팹
    
    // Start is called before the first frame update
    void Start()
    {
        InitMonster();//몬스터 생성
    }
    
    private void InitMonster()//몬스터 생성
    {
        mon = new GameObject[monsterCount];//몬스터 생성 숫자만큼 배열 할당
        
        for (int i = 0; i < monsterCount; i++)//몬스터 생성
        {
            string[] pos = monsterPos[i].Split(' ');//몬스터 위치 split
            if(!monsterBoss)
                mon[i] = Instantiate(Resources.Load("Monster/Prefabs/MonsterDummy")) as GameObject;//몬스터 더미(일반몬스터) 오브젝트생성
            //else
                //mon[i] = Instantiate(Resources.Load("Monster/Prefabs/MonsterBoss")) as GameObject;//몬스터 더미(보스) 오브젝트생성
            mon[i].transform.parent = transform;//MonsterManager의 자식으로 설정
            mon[i].transform.Find("Monster").GetComponent<Monster>().monsterNum = monsterNum;//몬스터 번호
            mon[i].transform.Find("Monster").GetComponent<Monster>().mNum = i;//몬스터 개인번호
            mon[i].transform.position = new Vector3(float.Parse(pos[0]), float.Parse(pos[1]), 0);//몬스터 해당위치로 이동
        }
    }

    public void DestroyMonster(int num)//몬스터 파괴(Monster.sc)에서 호출
    {
        StartCoroutine(ResponeMonster(num));//부활 코루틴
    }
    
    IEnumerator ResponeMonster(int num)//부활 코루틴
    {
        Destroy(mon[num]);//죽은 몬스터 오브젝트 제거
        if (responseTime == 0) yield break;//부활시간 0이면 부활x

        yield return new WaitForSeconds(responseTime);//부활시간만큼 대기

        string[] pos = monsterPos[num].Split(' ');//몬스터 위치 split
        if (!monsterBoss)
            mon[num] = Instantiate(Resources.Load("Monster/Prefabs/MonsterDummy")) as GameObject;//몬스터 더미(일반몬스터) 오브젝트생성
                                                                                               //else
                                                                                               //mon[num] = Instantiate(Resources.Load("Monster/Prefabs/MonsterBoss")) as GameObject;//몬스터 더미(보스) 오브젝트생성
        mon[num].transform.parent = transform;//MonsterManager의 자식으로 설정
        mon[num].transform.Find("Monster").GetComponent<Monster>().monsterNum = monsterNum;//몬스터 번호
        mon[num].transform.Find("Monster").GetComponent<Monster>().mNum = num;//몬스터 개인번호
        mon[num].transform.position = new Vector3(float.Parse(pos[0]), float.Parse(pos[1]), 0);//몬스터 해당위치로 이동
    }
}
