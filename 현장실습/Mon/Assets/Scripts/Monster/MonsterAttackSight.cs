﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterAttackSight : MonoBehaviour
{
    private GameObject monster;

    void Start()
    {
        monster = transform.parent.Find("Monster").gameObject;
    }

    void Update()
    {
        transform.position = monster.transform.position;
    }

    void OnTriggerEnter2D(Collider2D other)
    {
        if (other.gameObject.tag == "Player")
            monster.GetComponent<Monster>().attackSight = true;
    }

    void OnTriggerStay2D(Collider2D other)
    {
        if (other.gameObject.tag == "Player")
            monster.GetComponent<Monster>().attackSight = true;
    }

    void OnTriggerExit2D(Collider2D other)
    {
        if (other.gameObject.tag == "Player")
            monster.GetComponent<Monster>().attackSight = false;
    }
}
