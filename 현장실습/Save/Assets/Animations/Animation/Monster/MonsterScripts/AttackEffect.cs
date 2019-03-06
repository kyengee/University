using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AttackEffect : MonoBehaviour
{
    
    private GameObject player;
    // Start is called before the first frame update
    void Start()
    {
        player = GameObject.Find("Player");
        Vector3 pos = player.transform.position;
        pos.y -= 0.7f;
        transform.position = pos;
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 pos = player.transform.position;
        pos.y -= 0.7f;
        transform.position = pos;
    }

    private void EndEffect()
    {
        Destroy(gameObject);
    }

}
