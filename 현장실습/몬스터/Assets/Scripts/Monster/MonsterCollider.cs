using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterCollider : MonoBehaviour
{

    private Player player;
    private Monster monster;
    private Collider2D playerCollider;
    public bool destroy = false;
    private bool dir = false;

    
    // Start is called before the first frame update
    void Start()
    {
        player = GameObject.Find("Player").GetComponent<Player>();
        playerCollider = player.GetComponent<Collider2D>();
        monster = GameObject.Find("Monster").GetComponent<Monster>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void OnTriggerEnter2D(Collider2D other)
    {
        
        if (other.gameObject.tag == "Player")
        {
            if (!destroy)
            {
                if (player.transform.position.x < transform.position.x)
                {
                    dir = true;
                }
                else
                {
                    dir = false;
                }
                player.GetComponent<Player>().Hurt(dir, monster.power);//충돌 데미지
                GameObject damageUI = Instantiate(Resources.Load("UI/Prefabs/DamageUI")) as GameObject;//데미지UI 오브젝트생성
                damageUI.transform.parent = other.gameObject.transform.parent.transform;//Player오브젝트 자식으로 설정
                damageUI.GetComponent<DamageUI>().gameObj = other.gameObject;//Player오브젝트
                damageUI.GetComponent<DamageUI>().checkPlayer = true;//플레이어,몬스터 체크 true = 플레이어, false = 몬스터
                damageUI.transform.Find("Canvas").transform.Find("Damage").GetComponent<Damage>().damage = monster.power;//30데미지
                damageUI.transform.Find("Canvas").transform.Find("Damage").GetComponent<Damage>().color = "#ffff00ff";
            }
        }
    }

    void OnTriggerStay2D(Collider2D other)
    {
        if (other.gameObject.tag == "Player")
        {
            if (!destroy && !player.hurt)
            {
                if (player.transform.position.x < transform.position.x)
                {
                    dir = true;
                }
                else
                {
                    dir = false;
                }
                player.GetComponent<Player>().Hurt(dir, monster.power);//충돌 데미지
                GameObject damageUI = Instantiate(Resources.Load("UI/Prefabs/DamageUI")) as GameObject;//데미지UI 오브젝트생성
                damageUI.transform.parent = other.gameObject.transform.parent.transform;//Player오브젝트 자식으로 설정
                damageUI.GetComponent<DamageUI>().gameObj = other.gameObject;//Player오브젝트
                damageUI.GetComponent<DamageUI>().checkPlayer = true;//플레이어,몬스터 체크 true = 플레이어, false = 몬스터
                damageUI.transform.Find("Canvas").transform.Find("Damage").GetComponent<Damage>().damage = monster.power;//30데미지
                damageUI.transform.Find("Canvas").transform.Find("Damage").GetComponent<Damage>().color = "#ffff00ff";
            }
        }
    }

    public void DestroyObject()
    {
        Destroy(gameObject);
    }
}
