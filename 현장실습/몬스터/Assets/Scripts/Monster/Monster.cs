using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Monster : MonoBehaviour
{
    private Player player;
    public GameObject DropItem;
    private MonsterInfo monsterInfo;
    private GameObject monsterUI;

    private Rigidbody2D myRigidbody;
    private Animator myAnimator;
    private SpriteRenderer monsterSpriteRenderer;
    
    Coroutine corMove;
    Coroutine corAttack;
    Coroutine corHurt;

    //MonsterManager
    public int monsterNum;//몬스터 번호
    public int mNum;//몬스터 개인번호

    //MonsterInfo
    public bool moveType;//true 이동 false 고정
    public bool firstAttack;//true 선공 false 비선공
    public float attackTime;//공격시간
    public float attackDistance;//사정거리
    public int hp;//최대체력
    public int power;//공격력
    public int defence;//방어력
    public float moveSpeed;//이동속도
    public string dropItem;//1,44,2,33,5,6~
    
    private Vector2 colliderSize;//플레이어 점프시 MonsterSight콜라이더 변환용
    public int currentHp;//현재체력
    private bool first_Attack;//선공타입
    public int movementFlag = 0;//0 Idle, 1 Left이동, 2 Right이동, 3 LeftIdle, 4 RightIdle
    public bool direction = true;//몬스터 방향 true = Left, false = Right
    public bool superArmor = false;//몬스터 무적true = 무적, false = 무적해제
    private bool attack = false;//공격여부 true = 공격, false = 공격x
    private bool hurt = false;//피격여부 ture = 피격, false = 피격x
    private bool die = false;//죽음여부 ture = 죽음, false = 살아있음
    private bool checkMoveCor = false;//ChangeMovement실행여부 true = 실행, false = 실행x
    private bool checkAttackCor = false;//AttackMovement실행여부 true = 실행, false = 실행x
    
    void Start()
    {
        player = GameObject.Find("Player").GetComponent<Player>();
        monsterSpriteRenderer = GetComponent<SpriteRenderer>();
        myAnimator = GetComponent<Animator>();

        Physics2D.IgnoreCollision(GetComponent<Collider2D>(), GameObject.Find("Player").GetComponent<Collider2D>(), true);//Player과 충돌무시

        monsterInfo = GameObject.Find("MonsterInfo").GetComponent<MonsterInfo>();
        monsterInfo.SetMonster(gameObject, monsterUI);//몬스터 정보 설정
        
        colliderSize = transform.parent.Find("MonsterSight").GetComponent<BoxCollider2D>().size;//MonsterSight콜라이더박스 기억
        monsterSpriteRenderer.color = new Color32(255, 255, 255, 0);//시작시 투명도 0
        StartCoroutine(FadeIn());//몬스터 생성시 슈퍼아머 FadeIn코루틴 (2초)
        currentHp = hp;//현재 체력을 최대체력으로 맞춤
        first_Attack = firstAttack;//선공타입 기억
       
        if (moveType)//이동몹
            corMove = StartCoroutine(ChangeMovement());//몬스터 이동AI (3초)
        else//고정몹
            movementFlag = UnityEngine.Random.Range(3, 5);//(3,4) 0 Idle, 1 Left이동, 2 Right이동, 3 LeftIdle, 4 RightIdle
    }
    
    void Update()
    {
        Move();//이동
        CheckHp();//체력확인
    }
    
    void Move()//이동
    {
        Vector3 moveVelocity = Vector3.zero;
        Vector3 theScale = transform.localScale;//현재 scale기억
        switch (movementFlag)//0 Idle, 1 Left이동, 2 Right이동, 3 LeftIdle, 4 RightIdle
        {
            case 0:
                moveVelocity = Vector3.zero;//(0, 0, 0)
                break;
            case 1:
                moveVelocity = Vector3.left;//(-1, 0, 0)
                direction = true;//몬스터 방향 true = Left, false = Right
                break;
            case 2:
                moveVelocity = Vector3.right;//(1, 0, 0)
                direction = false;//몬스터 방향 true = Left, false = Right
                break;
            case 3:
                moveVelocity = Vector3.zero;//(0, 0, 0)
                direction = true;//몬스터 방향 true = Left, false = Right
                break;
            case 4:
                moveVelocity = Vector3.zero;//(0, 0, 0)
                direction = false;//몬스터 방향 true = Left, false = Right
                break;
        }
        if (direction)//몬스터 방향 true = Left, false = Right
        {
            if (theScale.x < 0)//양수면 왼쪽, 음수면 오른쪽
            {
                theScale.x *= -1;//왼쪽방향인데 이미지가 오른쪽일때
            }
        }
        else
        {
            if (theScale.x > 0)//양수면 왼쪽, 음수면 오른쪽
            {
                theScale.x *= -1;//오른쪽방향인데 이미지가 왼쪽일때
            }
        }
        transform.localScale = theScale;//scale 수정(방향맞춰서)
        transform.position += moveVelocity * moveSpeed * Time.deltaTime;//좌표이동
    }
    
    public void TargetIn(Collider2D other)//MonsterSight안에 들어왔을때
    {
        if (first_Attack)//선공 or 체력달았을 때
        {
            if (player.transform.position.x < transform.position.x)
            {
                if (moveType)//이동
                    movementFlag = 1;//0 Idle, 1 Left이동, 2 Right이동, 3 LeftIdle, 4 RightIdle
                else
                    movementFlag = 3;//0 Idle, 1 Left이동, 2 Right이동, 3 LeftIdle, 4 RightIdle
            }
            else
            {
                if (moveType)//이동
                    movementFlag = 2;//0 Idle, 1 Left이동, 2 Right이동, 3 LeftIdle, 4 RightIdle
                else
                    movementFlag = 4;//0 Idle, 1 Left이동, 2 Right이동, 3 LeftIdle, 4 RightIdle
            }
            if (moveType)//이동
                myAnimator.SetBool("move", true);
            attack = false;//공격여부 true = 공격, false = 공격x
        }
    }

    public void TargetStay(Collider2D other)//MonsterSight안에 있을때
    {
        if (first_Attack)//선공 or 체력달았을 때
        {
            BoxCollider2D monster = transform.parent.Find("MonsterSight").GetComponent<BoxCollider2D>();

            if (!player.isGrounded)//플레이어 점프시
                monster.size = new Vector2(colliderSize.x, colliderSize.y * 4);//MonsterSight y축만 4배
            else//플레이어 땅에있음
                monster.size = colliderSize;//MonsterSight 원래대로

            if (moveType && currentHp < hp && !checkMoveCor)//이동식 && 체력달아있음 && ChangeMovement실행x
            {
                StopCoroutine(corMove);//ChangeMovement코루틴 종료
                checkMoveCor = true;//ChangeMovement실행여부 true = 실행, false = 실행x
            }

            //-------------------------------------------------------------------------------------------------------------------

            //Debug.Log(Mathf.Abs(player.transform.position.x - transform.position.x));//사정거리 측정용 Log

            //-------------------------------------------------------------------------------------------------------------------

            //트리거 계속 실행시킬 꼼수
            Vector3 pos = transform.position;
            pos.y += 0.0001f;
            transform.position = pos;
            //트리거 계속 실행시킬 꼼수

            if (Mathf.Abs(player.transform.position.x - transform.position.x) < attackDistance)//사정거리 안
            {
                if (player.transform.position.x < transform.position.x)//위치  플레이어 - 몬스터
                    movementFlag = 3;//0 Idle, 1 Left이동, 2 Right이동, 3 LeftIdle, 4 RightIdle
                else//위치  몬스터 - 플레이어
                    movementFlag = 4;//0 Idle, 1 Left이동, 2 Right이동, 3 LeftIdle, 4 RightIdle
                if (moveType)//이동식
                    myAnimator.SetBool("move", false);
                attack = true;//공격여부 true = 공격, false = 공격x
            }
            else//사정거리 밖
            {
                if (player.transform.position.x < transform.position.x)//위치  플레이어 - 몬스터
                {
                    if (moveType)//이동식
                        movementFlag = 1;//0 Idle, 1 Left이동, 2 Right이동, 3 LeftIdle, 4 RightIdle
                    else
                        movementFlag = 3;//0 Idle, 1 Left이동, 2 Right이동, 3 LeftIdle, 4 RightIdle
                }
                else//위치  몬스터 - 플레이어
                {
                    if (moveType)//이동식
                        movementFlag = 2;//0 Idle, 1 Left이동, 2 Right이동, 3 LeftIdle, 4 RightIdle
                    else
                        movementFlag = 4;//0 Idle, 1 Left이동, 2 Right이동, 3 LeftIdle, 4 RightIdle
                }
                if (moveType)//이동식
                    myAnimator.SetBool("move", true);
                attack = false;//공격여부 true = 공격, false = 공격x
            }
        }
    }

    public void TargetOut(Collider2D other)//MonsterSight 나갔을때
    {
        if (moveType)//이동식
        {
            if (currentHp < hp)//체력 달아있음
            {
                corMove = StartCoroutine(ChangeMovement());//몬스터 이동AI (3초)
                checkMoveCor = false;//ChangeMovement실행여부 true = 실행, false = 실행x
            }
            if (!firstAttack)//체력 달아있는 상태였다면
                first_Attack = firstAttack;//원래 선공타입으로 변경
        }
        attack = false;//공격여부 true = 공격, false = 공격x
        currentHp = hp;//체력 회복
        StopCoroutine(AttackTimer());//AttackTimer코루틴 종료
    }

    void CheckHp()//체력확인
    {
        if (!die)//죽음여부 ture = 죽음, false = 살아있음
        {
            if (currentHp <= 0)//현재 체력이 0이하(사망)
            {
                monsterSpriteRenderer.color = new Color32(255, 255, 255, 255);//투명도 원상복귀
                die = true;//죽음여부 ture = 죽음, false = 살아있음
                hurt = false;//피격여부 ture = 피격, false = 피격x
                movementFlag = 0;//0 Idle, 1 Left이동, 2 Right이동, 3 LeftIdle, 4 RightIdle

                if (moveType)//이동식
                    StopCoroutine(corMove);//ChangeMovement코루틴 종료
                StopCoroutine(corHurt);//HurtTimer코루틴 종료
                StopCoroutine(corAttack);//HurtTimer코루틴 종료
                myAnimator.SetBool("hurt", false);
                myAnimator.SetTrigger("die");
                myAnimator.SetBool("move", false);
                myAnimator.SetBool("attack", false);

                transform.parent.Find("MonsterCollider").GetComponent<MonsterCollider>().DestroyObject();//MonsterCollider 삭제
                monsterUI.SetActive(false);//몬스터UI안보이게
            }
            if (currentHp < hp)//체력이 달아있으면
                first_Attack = true;//선공으로 변경
        }
    }

    public void Hurt(int damage)//Player에서 호출
    {
        if (!hurt)//피격여부 ture = 피격, false = 피격x
        {
            currentHp -= damage;//데미지만큼 체력감소
            hurt = true;//피격여부 ture = 피격, false = 피격x
            myAnimator.SetBool("hurt", true);
            corHurt = StartCoroutine(HurtTimer());//피격시 투명도 코루틴 (1초)
        }
    }

    private void DestroyMonster()//Monster_Die애니메이션에서 호출
    {
        transform.parent.transform.parent.GetComponent<MonsterManager>().DestroyMonster(mNum);//MonsterManager에 본인 번호 전송
        string[] stringItem = dropItem.Split(',');//','단위로 분할
        for (int i = 0; i < stringItem.Length; i++)
        {
            GameObject item = Instantiate(DropItem) as GameObject;
            item.GetComponent<DropItem>().c = int.Parse(stringItem[i]);//해당번호로 초기화
        }
    }

    public void CreateAttackEffect()//AttackEffect 애니메이션에서 호출
    {
        //어텍이펙트가 잇으면
        GameObject AttackEffect = Instantiate(Resources.Load("Monster/Prefabs/MonsterAttackEffect")) as GameObject;//몬스터공격이펙트 오브젝트생성
        AttackEffect.GetComponent<MonsterAttackEffect>().monsterNum = monsterNum;//몬스터 번호 동기화
    }

    IEnumerator FadeIn()//몬스터 생성시 슈퍼아머 FadeIn코루틴 (2초)
    {
        int time = 1;
        superArmor = true;//슈퍼아머 설정
        while (time <= 20)
        {
            monsterSpriteRenderer.color = new Color32(255, 255, 255, (byte)(time * 12));//투명도 12 * (1~20)
            yield return new WaitForSeconds(0.1f);
            time++;
        }
        monsterSpriteRenderer.color = new Color32(255, 255, 255, 255);//투명도 원상복귀
        superArmor = false;//슈퍼아머 해제
    }

    IEnumerator ChangeMovement()//몬스터 이동AI (3초)
    {
        yield return new WaitForSeconds(3f);
        movementFlag = UnityEngine.Random.Range(0, 3);//(0, 1, 2) 0 Idle, 1 Left이동, 2 Right이동, 3 LeftIdle, 4 RightIdle
        if (movementFlag == 0)
            myAnimator.SetBool("move", false);
        else
            myAnimator.SetBool("move", true);
        corMove = StartCoroutine(ChangeMovement());//몬스터 이동AI (3초)
    }

    IEnumerator AttackTimer()//공격 딜레이 코루틴(attackTime + 0.1초)
    {
        if (attack)//공격여부 true = 공격, false = 공격x
            myAnimator.SetBool("attack", true);
        yield return new WaitForSeconds(0.1f);
        myAnimator.SetBool("attack", false);
        yield return new WaitForSeconds(attackTime);

        corAttack = StartCoroutine(AttackTimer());//공격 딜레이 코루틴(attackTime + 0.1초)
    }

    IEnumerator HurtTimer()//피격시 투명도 코루틴 (1초)
    {
        for(int i = 0; i<10; i++)
        {
            if(i % 2 == 0)
                monsterSpriteRenderer.color = new Color32(255, 255, 255, 100);//투명도100
            else
                monsterSpriteRenderer.color = new Color32(255, 255, 255, 255);//투명도255
            yield return new WaitForSeconds(0.1f);
        }
        myAnimator.SetBool("hurt", false);
        hurt = false;//피격여부 ture = 피격, false = 피격x
        if (!checkAttackCor)//AttackMovement실행여부 true = 실행, false = 실행x
        {
            checkAttackCor = true;//AttackMovement실행여부 true = 실행, false = 실행x
            corAttack = StartCoroutine(AttackTimer());//공격 딜레이 코루틴(attackTime + 0.1초)
        }
    }
}
