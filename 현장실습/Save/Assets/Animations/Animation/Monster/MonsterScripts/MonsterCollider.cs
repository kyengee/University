using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterCollider : MonoBehaviour
{

    private Player player;
    public bool destroy = false;
    private bool dir = false;
    // Start is called before the first frame update
    void Start()
    {
        player = GameObject.Find("Player").GetComponent<Player>();
    }

    // Update is called once per frame
    void Update()
    {
        transform.position = transform.parent.Find("Monster").transform.position;
    }


    void OnTriggerStay2D(Collider2D other)
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
                player.GetComponent<Player>().Hurt(dir, transform.parent.Find("Monster").GetComponent<Monster>().power);//충돌 데미지
            }
        }
    }
}
