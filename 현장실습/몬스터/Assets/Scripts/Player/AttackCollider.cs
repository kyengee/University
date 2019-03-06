using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AttackCollider : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void OnTriggerEnter2D(Collider2D other)
    {
        if (other.gameObject.tag == "Monster")
        {
            Monster monster = other.gameObject.transform.parent.GetComponent<Monster>();
            if (!monster.superArmor)
            {
                monster.Hurt(30);//30데미지
                GameObject damageUI = Instantiate(Resources.Load("UI/Prefabs/DamageUI")) as GameObject;//데미지UI 오브젝트생성
                damageUI.transform.parent = other.gameObject.transform.parent.transform.parent.transform;
                damageUI.GetComponent<DamageUI>().gameObj = other.gameObject.transform.parent.gameObject;
                damageUI.GetComponent<DamageUI>().checkPlayer = false;//플레이어,몬스터 체크 true = 플레이어, false = 몬스터
                damageUI.transform.Find("Canvas").transform.Find("Damage").GetComponent<Damage>().damage = 30;//30데미지
                damageUI.transform.Find("Canvas").transform.Find("Damage").GetComponent<Damage>().color = "#ffff00ff";
                Vector3 pos = monster.transform.position;
                if (transform.position.x - pos.x < 0)
                {
                    monster.direction = true;
                    if (monster.moveType)
                        pos.x += 0.1f;
                }
                else
                {
                    monster.direction = false;
                    if (monster.moveType)
                        pos.x -= 0.1f;
                }
                monster.transform.position = pos;
            }
        }
    }
}
