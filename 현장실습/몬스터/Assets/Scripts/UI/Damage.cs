using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class Damage : MonoBehaviour
{
    private Text text;
    public int damage;
    public string color;
    private Vector3 pos;
    public bool target;
    // Start is called before the first frame update
    void Start()
    {
        text = GetComponent<Text>();
        text.text = "<color=" + color.Remove(7) + "10" + ">" + Convert.ToString(damage) + "</color>";
        pos = transform.position;
        StartCoroutine(DamageTimer());//데미지 이동,알파값 코루틴
    }
    // Update is called once per frame
    void Update()
    {
        
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
                color = color.Remove(7) + tmp;
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
                color = color.Remove(7) + tmp;
                text.text = "<color=" + color + ">" + Convert.ToString(damage) + "</color>";
            }
            transform.position = new Vector3(transform.position.x, pos.y + Mathf.Sin(theta * Mathf.Deg2Rad) + 1);
            yield return new WaitForSeconds(0.0005f);
            theta += 5;
        }
        Destroy(transform.parent.transform.parent.gameObject);
    }
}
