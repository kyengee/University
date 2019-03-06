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
                player.GetComponent<Player>().Hurt(dir, monster.power, "YELLOW");//충돌 데미지
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
                player.GetComponent<Player>().Hurt(dir, monster.power, "YELLOW");//충돌 데미지
            }
        }
    }

    public void DestroyObject()
    {
        Physics2D.IgnoreCollision(GetComponent<Collider2D>(), GameObject.Find("Player").GetComponent<Collider2D>(), true);//Player과 충돌무시
    }
}
