using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class Damage : MonoBehaviour
{
    private Text text;
    public int damage;
    public string colorName = "YELLOW";
    private string color = "#ffff0000";
    private Vector3 pos;
    // Start is called before the first frame update\
    void Awake()
    {
        text = GetComponent<Text>();
        text.text = "<color=#ffff0000>0</color>";
    }
    void Start()
    {
        pos = transform.position;
        StartCoroutine(DamageTimer());//데미지 이동,알파값 코루틴
    }

    // Update is called once per frame
    void Update()
    {

        SetColor(colorName);
    }

    private void SetColor(string colorName)
    {
        string strTmp = "";
        switch (colorName)
        {
            case "RED":
                strTmp = "#ff0000";
                break;
            case "YELLOW":
                strTmp = "#ffff00";
                break;
            case "GREEN":
                strTmp = "#00ff00";
                break;
            case "BLACK":
                strTmp = "#ffffff";
                break;
        }
        color = strTmp + text.text.Substring(14, 2);
        text.text = "<color=" + color + ">" + damage + "</color>";
    }
    IEnumerator DamageTimer()//데미지 이동코루틴
    {
        int theta = 0;
        string tmp;
        while (theta <= 90)
        {
            if(theta % 10 != 0)
            {
                tmp = Convert.ToString(Convert.ToByte(75 + theta * 2), 16);
                color = color.Substring(0, 7) + tmp;
                text.text = "<color=" + color + ">" + Convert.ToString(damage) + "</color>";
            }
            transform.position = new Vector3(transform.position.x, pos.y + Mathf.Sin(theta * Mathf.Deg2Rad) + 1);
            yield return new WaitForSeconds(0.0005f);
            theta += 5;
        }
        theta = -90;
        pos = transform.position;
        while (theta <= 0)
        {
            if (theta % 10 != 0)
            {
                tmp = Convert.ToString(Convert.ToByte(75 + theta * -2), 16);
                color = color.Substring(0, 7) + tmp;
                text.text = "<color=" + color + ">" + Convert.ToString(damage) + "</color>";
            }
            transform.position = new Vector3(transform.position.x, pos.y + Mathf.Sin(theta * Mathf.Deg2Rad) + 1);
            yield return new WaitForSeconds(0.0005f);
            theta += 5;
        }
        Destroy(transform.parent.transform.parent.gameObject);
    }
}
