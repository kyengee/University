using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterAttackEffect : MonoBehaviour
{
    
    private GameObject player;
    public int monsterNum;//몬스터 번호
    public Vector3 setPos;//AttackEffectPosition 
    public int damage;

    // Start is called before the first frame update
    void Start()
    {
        player = GameObject.Find("Player");

        GetComponent<Animator>().runtimeAnimatorController = Resources.Load("Monster/AnimationControllers/" + Convert.ToString(monsterNum) + "/" + Convert.ToString(monsterNum) + "AttackEffect") as RuntimeAnimatorController;//애니메니터 몬스터 번호에 맞춰서 설정
        
        transform.position = player.transform.position + setPos;//AttackEffectPosition 
        GameObject damageUI = Instantiate(Resources.Load("UI/Prefabs/DamageUI")) as GameObject;//데미지UI 오브젝트생성
        damageUI.GetComponent<DamageUI>().SetDamage(player, damage, "YELLOW");

    }

    // Update is called once per frame
    void Update()
    {
        transform.position = player.transform.position + setPos;//AttackEffectPosition 
    }

    private void EndEffect()//이펙트 애니메이션 종료
    {
        Destroy(gameObject);//오브젝트 삭제
    }

}
