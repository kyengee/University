using System.Collections;
using System.Collections.Generic;
using UnityEngine;



public class DamageUI : MonoBehaviour
{
    private GameObject gameObj;
    public bool checkPlayer;//플레이어,몬스터 체크 true = 플레이어, false = 몬스터

    // Start is called before the first frame update
    void Start()
    {
    }

    // Update is called once per frame
    void Update()
    {
        transform.position = gameObj.transform.position;
    }

    
    public void SetDamage(GameObject gameObj, int damage, string color)
    {
        this.gameObj = gameObj;
        transform.Find("Canvas").transform.Find("Damage").GetComponent<Damage>().damage = damage;//30데미지
        transform.Find("Canvas").transform.Find("Damage").GetComponent<Damage>().colorName = color;
    }
}