using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DamageUI : MonoBehaviour
{
    public GameObject gameObj;

    public bool checkPlayer;//플레이어,몬스터 체크 true = 플레이어, false = 몬스터
    // Start is called before the first frame update
    void Start()
    {
        if(checkPlayer)//플레이어,몬스터 체크 true = 플레이어, false = 몬스터
            gameObj = GameObject.Find("Player").gameObject; 
        else
            gameObj = transform.parent.transform.Find("Monster").gameObject;
    }

    // Update is called once per frame
    void Update()
    {
        transform.position = gameObj.transform.position;
    }
}
