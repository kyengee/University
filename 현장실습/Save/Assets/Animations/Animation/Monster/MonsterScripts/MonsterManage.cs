using System.Collections;
using System.Collections.Generic;
using UnityEngine;



public class MonsterManage : MonoBehaviour
{
    static int monsterNum = 10;
    public GameObject Monster;
    GameObject[] mon = new GameObject[monsterNum];
    // Start is called before the first frame update
    void Start()
    {
        for (int i = 0; i < monsterNum; i++)//몬스터 생성
        {
            mon[i] = Instantiate(Monster) as GameObject;
            mon[i].transform.parent = this.transform;
        }




        //몬스터 위치
        mon[0].transform.position = new Vector3(3, 0, 0);


        for (int i = 0; i < monsterNum; i++)//몬스터 식별번호
            mon[i].transform.Find("Monster").GetComponent<Monster>().monsterNum = i;
    }

    // Update is called once per frame
    void Update()
    {

    }

    public void DestroyMonster(int num)
    {
        Destroy(mon[num]);
        StartCoroutine(ResponeMonster(num));
    }


    IEnumerator ResponeMonster(int num)
    {
        yield return new WaitForSeconds(3f);
        mon[num] = Instantiate(Monster) as GameObject;
        mon[num].transform.parent = this.transform;
        mon[num].transform.Find("Monster").GetComponent<Monster>().monsterNum = num;
    }
}
