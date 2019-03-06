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
                monster.Hurt(30, "YELLOW");//30데미지
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
