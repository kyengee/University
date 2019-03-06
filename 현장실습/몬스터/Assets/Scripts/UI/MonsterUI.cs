using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MonsterUI : MonoBehaviour
{
    private Image healthBarFilled;
    private Monster monster;
    // Start is called before the first frame update
    void Start()
    {
        monster = transform.parent.Find("Monster").GetComponent<Monster>();
        healthBarFilled = transform.Find("Canvas").transform.Find("BackgroundBar").Find("HealthBarFilled").GetComponent<Image>();
        healthBarFilled.fillAmount = 1f;//체력바 가득채움
    }

    // Update is called once per frame
    void Update()
    {
        transform.position = transform.parent.Find("Monster").transform.position;
        healthBarFilled.fillAmount = (float)monster.currentHp / monster.hp;
    }
}
