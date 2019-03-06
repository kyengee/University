using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class Monster : MonoBehaviour
{
    private Rigidbody2D myRigidbody;
    private Animator myAnimator;

    private Player player;
    public GameObject healthBarBackground;
    public Image healthBarFilled;
    public GameObject attackEffectObj;
    private SpriteRenderer monsterSpriteRenderer;
    public GameObject DropItem;

    Coroutine corMove;
    Coroutine corAttack;
    Coroutine corHurt;


    [SerializeField]
    public bool moveType;//true 이동 false 고정
    [SerializeField]
    private bool firstAttack;//true 선공 false 비선공
    [SerializeField]
    private float attackDistance;//사정거리
    [SerializeField]
    private float attackTime;//공격시간
    [SerializeField]
    private int hp;//체력
    [SerializeField]
    public int power;//공격력
    [SerializeField]
    private int defence;//방어력
    [SerializeField]
    private float moveSpeed;//이동속도
    [SerializeField]
    private float attackMoveSpeed;//이동속도
    [SerializeField]
    private string dropItem;//1,44,2,33,5,6~

    public int monsterNum;
    public bool direction = true;
    private bool attack = false;
    public int currentHp;//현재체력
    private float movespeed;//이동속도
    public int movementFlag = 0;//0 Idle 1 LeftMove 2 RightMove
    private bool first_Attack;
    private Vector2 colliderSize;
    private bool stopCor = false;
    private bool hurt = false;

    // Start is called before the first frame update
    void Start()
    {
        first_Attack = firstAttack;
        player = GameObject.Find("Player").GetComponent<Player>();
        currentHp = hp;
        movespeed = moveSpeed;
        myAnimator = GetComponentInChildren<Animator>();
        healthBarFilled.fillAmount = 1f;
        if (moveType)
            corMove = StartCoroutine(ChangeMovement());
        else
            movementFlag = Random.Range(3, 5);

        monsterSpriteRenderer = GetComponent<SpriteRenderer>();


        BoxCollider2D monster = GetComponent<BoxCollider2D>();
        colliderSize = monster.size;
        corAttack = StartCoroutine(AttackTimer());

    }

    // Update is called once per frame
    void Update()
    {
        Move();
        CheckHp();
    }

    public void CreateAttackEffect()
    {
        GameObject AttackEffect = Instantiate(attackEffectObj) as GameObject;
    }

    
    void Move()
    {
        Vector3 moveVelocity = Vector3.zero;
        Vector3 theScale = transform.localScale;
        Vector3 healthBarScale = healthBarBackground.transform.localScale;
        switch (movementFlag)
        {
            case 0:
                moveVelocity = Vector3.zero;
                break;
            case 1:
                moveVelocity = Vector3.left;
                direction = true;
                break;
            case 2:
                moveVelocity = Vector3.right;
                direction = false;
                break;
            case 3:
                moveVelocity = Vector3.zero;
                direction = true;
                break;
            case 4:
                moveVelocity = Vector3.zero;
                direction = false;
                break;
        }
        if (direction)
        {
            if (theScale.x < 0)
            {
                theScale.x *= -1;
                healthBarScale.x *= -1;
            }
        }
        else
        {
            if (theScale.x > 0)
            {
                theScale.x *= -1;
                healthBarScale.x *= -1;
            }
        }

        transform.localScale = theScale;
        healthBarBackground.transform.localScale = healthBarScale;
        transform.position += moveVelocity * movespeed * Time.deltaTime;
    }
    
    void OnTriggerEnter2D(Collider2D other)
    {
        
        if (first_Attack)//선공
        {
            if (other.gameObject.tag == "Player")
            {
                
                movespeed = moveSpeed * attackMoveSpeed;
                if (player.transform.position.x < transform.position.x)
                {
                    if (moveType)//이동
                        movementFlag = 1;
                    else
                        movementFlag = 3;
                }
                else
                {
                    if (moveType)//이동
                        movementFlag = 2;
                    else
                        movementFlag = 4;
                }
                if (moveType)//이동
                    myAnimator.SetBool("move", true);
                attack = false;
            }
        }
    }

    void OnTriggerStay2D(Collider2D other)
    {
        if (first_Attack)//선공
        {
            if (moveType && currentHp < hp && !stopCor)//이동
            {
                StopCoroutine(corMove);
                stopCor = true;
            }
            if (other.gameObject.tag == "Player")
            {
                BoxCollider2D monster = GetComponent<BoxCollider2D>();
                if (!player.isGrounded)
                    monster.size = new Vector2(colliderSize.x, colliderSize.y * 3);
                else
                    monster.size = colliderSize;
                movespeed = moveSpeed * attackMoveSpeed;
                //----------------------------------------------------------------------------------
                //Debug.Log(Mathf.Abs(player.transform.position.x - transform.position.x));
                //----------------------------------------------------------------------------------
                Vector3 theScale = transform.localScale;
                Vector3 pos = transform.position;
                pos.y += 0.0001f;
                transform.position = pos;
                if (Mathf.Abs(player.transform.position.x - transform.position.x) < attackDistance)
                {
                    if (player.transform.position.x < transform.position.x)
                    {
                        movementFlag = 3;
                    }
                    else
                    {
                        movementFlag = 4;
                    }
                    if (moveType)//이동식
                        myAnimator.SetBool("move", false);
                    attack = true;
                }
                else
                {
                    if (player.transform.position.x < transform.position.x)
                    {
                        if (moveType)//이동식
                            movementFlag = 1;
                        else
                            movementFlag = 3;
                    }
                    else
                    {
                        if (moveType)//이동식
                            movementFlag = 2;
                        else
                            movementFlag = 4;
                    }
                    if (moveType)//이동식
                        myAnimator.SetBool("move", true);
                    attack = false;
                }
            }
        }
    }

    void OnTriggerExit2D(Collider2D other)
    {
        if(other.gameObject.tag == "Player")
        {
            if (moveType)//이동식
            {
                movespeed = moveSpeed;
                if (currentHp < hp)
                {
                    corMove = StartCoroutine(ChangeMovement());
                    stopCor = false;
                }
                if (!firstAttack)
                    first_Attack = firstAttack;
            }
            attack = false;
            currentHp = hp; 
            StopCoroutine(AttackTimer());
        }
    }

    void CheckHp()
    {
        if(currentHp <= 0)
        {
            transform.parent.Find("MonsterCollider").transform.GetComponent<MonsterCollider>().destroy = true;
            myAnimator.SetTrigger("die");
            myAnimator.SetBool("move", false);
            myAnimator.SetBool("attack", false);
            movementFlag = 0;
            if (moveType)//이동식
                StopCoroutine(corMove);
            healthBarBackground.SetActive(false);
        }
        if (currentHp < hp)
            first_Attack = true;
        healthBarFilled.fillAmount = (float)currentHp / hp;
    }

    public void Hurt()
    {
        if (!hurt)
        {
            hurt = true;
            myAnimator.SetBool("hurt", true);
            corHurt = StartCoroutine(HurtTimer());
        }
    }

    private void DestroyMonster()
    {
        transform.parent.transform.parent.GetComponent<MonsterManage>().DestroyMonster(monsterNum);
        string[] item = dropItem.Split(',');
        for (int i = 0; i < item.Length; i++)
        {
            GameObject a = Instantiate(DropItem) as GameObject;
            a.GetComponent<DropItem>().c = int.Parse(item[i]);
        }
    }

    IEnumerator ChangeMovement()
    {
        yield return new WaitForSeconds(3f);
        movementFlag = Random.Range(0, 3);
        if (movementFlag == 0)
            myAnimator.SetBool("move", false);
        else
            myAnimator.SetBool("move", true);
        corMove = StartCoroutine(ChangeMovement());
    }

    IEnumerator AttackTimer()
    {
        if (attack)
            myAnimator.SetBool("attack", true);
        yield return new WaitForSeconds(Random.Range(1, 2));
        myAnimator.SetBool("attack", false);
        yield return new WaitForSeconds(attackTime);
        corAttack = StartCoroutine(AttackTimer());
    }

    IEnumerator HurtTimer()
    {
        monsterSpriteRenderer.color = new Color(monsterSpriteRenderer.color.r, monsterSpriteRenderer.color.g, monsterSpriteRenderer.color.b, monsterSpriteRenderer.color.a / 2);
        yield return new WaitForSeconds(0.1f);
        monsterSpriteRenderer.color = new Color(monsterSpriteRenderer.color.r, monsterSpriteRenderer.color.g, monsterSpriteRenderer.color.b, monsterSpriteRenderer.color.a * 2);
        yield return new WaitForSeconds(0.1f);
        monsterSpriteRenderer.color = new Color(monsterSpriteRenderer.color.r, monsterSpriteRenderer.color.g, monsterSpriteRenderer.color.b, monsterSpriteRenderer.color.a / 2);
        yield return new WaitForSeconds(0.1f);
        monsterSpriteRenderer.color = new Color(monsterSpriteRenderer.color.r, monsterSpriteRenderer.color.g, monsterSpriteRenderer.color.b, monsterSpriteRenderer.color.a * 2);
        yield return new WaitForSeconds(0.1f);
        monsterSpriteRenderer.color = new Color(monsterSpriteRenderer.color.r, monsterSpriteRenderer.color.g, monsterSpriteRenderer.color.b, monsterSpriteRenderer.color.a / 2);
        yield return new WaitForSeconds(0.1f);
        monsterSpriteRenderer.color = new Color(monsterSpriteRenderer.color.r, monsterSpriteRenderer.color.g, monsterSpriteRenderer.color.b, monsterSpriteRenderer.color.a * 2);
        yield return new WaitForSeconds(0.5f);
        myAnimator.SetBool("hurt", false);
        hurt = false;
    }
}
