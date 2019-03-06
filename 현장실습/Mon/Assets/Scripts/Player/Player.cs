using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    Coroutine corAttack;

    private Rigidbody2D myRigidbody;
    private Animator myAnimator;

    private Animator headAnimator;
    private Animator bodyAnimator;
    private Animator leftLegAnimator;
    private Animator rightLegAnimator;
    private Animator helmetAnimator;
    private Animator shieldAnimator;
    private Animator swordAnimator;

    private SpriteRenderer headSpriteRenderer;
    private SpriteRenderer bodySpriteRenderer;
    private SpriteRenderer leftSpriteRenderer;
    private SpriteRenderer rightLegSpriteRenderer;
    private SpriteRenderer helmetSpriteRenderer;
    private SpriteRenderer shieldSpriteRenderer;
    private SpriteRenderer swordSpriteRenderer;

    private GameObject attackCollider;
    
    [SerializeField]
    private float movementSpeed;
    //stat
    [SerializeField]
    private int Hp = 100;


    //move
    public bool facingLeft = true;

    //jump
    public bool isGrounded;
    public Transform groundCheck;
    private int extraJumps;
    public int extraJumpsValue;
    public float checkRadius;
    public LayerMask whatIsGround;
    public float jumpForce;

    //hurt
    public bool hurt = false;

    //stat
    public bool superArmor = false;//캐릭터 무적(true = 무적, false = 무적해제)
    public int currentHp = 100;
    
    
    // Start is called before the first frame update
    void Start()
    {
        myRigidbody = GetComponent<Rigidbody2D>();
        myAnimator = GetComponent<Animator>();
        headAnimator = GameObject.Find("Head").GetComponent<Animator>();
        bodyAnimator = GameObject.Find("Body").GetComponent<Animator>();
        leftLegAnimator = GameObject.Find("LeftLeg").GetComponent<Animator>();
        rightLegAnimator = GameObject.Find("RightLeg").GetComponent<Animator>();
        helmetAnimator = GameObject.Find("Helmet").GetComponent<Animator>();
        shieldAnimator = GameObject.Find("Shield").GetComponent<Animator>();
        swordAnimator = GameObject.Find("Sword").GetComponent<Animator>();

        headSpriteRenderer = GameObject.Find("Head").GetComponent<SpriteRenderer>();
        bodySpriteRenderer = GameObject.Find("Body").GetComponent<SpriteRenderer>();
        leftSpriteRenderer = GameObject.Find("LeftLeg").GetComponent<SpriteRenderer>();
        rightLegSpriteRenderer = GameObject.Find("RightLeg").GetComponent<SpriteRenderer>();
        helmetSpriteRenderer = GameObject.Find("Helmet").GetComponent<SpriteRenderer>();
        shieldSpriteRenderer = GameObject.Find("Shield").GetComponent<SpriteRenderer>();
        swordSpriteRenderer = GameObject.Find("Sword").GetComponent<SpriteRenderer>();


        attackCollider = GameObject.Find("AttackCollider");
        attackCollider.SetActive(false);
        extraJumps = extraJumpsValue;

    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.LeftShift)){
            corAttack = StartCoroutine(AttackCollider());
            SetTriggerAttack(true);
        }


        if (isGrounded == true) // 캐릭터가 지면일때 
        {
            SetTriggerJumpStart(false);
            SetBoolJumpEnd(true);
            extraJumps = extraJumpsValue; // extrajumps를 설정한 extraJumpValue로 초기화
        }
        else
        {
            SetBoolJumpEnd(false);
            SetTriggerAttack(false);
        }
        if (Input.GetKeyDown(KeyCode.LeftControl) && extraJumps > 0) //점프키를 눌렀을때 extraJumps가 0이상이면
        {
            extraJumps--;
            StartCoroutine(JumpTimer());
        }
        else if (Input.GetKeyDown(KeyCode.LeftControl) && extraJumps == 0 && isGrounded == true)
        {
            StartCoroutine(JumpTimer());
        }
    }

    void FixedUpdate()
    {
        float horizontal = Input.GetAxis("Horizontal");
        isGrounded = Physics2D.OverlapCircle(groundCheck.position, checkRadius, whatIsGround);

        HandleMovement(horizontal);
        Flip(horizontal);
    }




    private void HandleMovement(float horizontal)
    {
        myRigidbody.velocity = new Vector2(horizontal * movementSpeed, myRigidbody.velocity.y);
        if (horizontal == 0)
        {
            SetBoolMove(false);
        }
        else
        {
            SetBoolMove(true);
        }
    }


    private void Flip(float horizontal)
    {
        if (isGrounded == true && (horizontal != 0 &&(horizontal < 0 && !facingLeft || horizontal > 0 && facingLeft)))
        {
            facingLeft = !facingLeft;
            Vector3 theScale = transform.localScale;
            theScale.x *= -1;
            transform.localScale = theScale;
        }
    }

    public void Hurt(bool monPos, int damage, string color)
    {
        if (!hurt)
        {
            GameObject damageUI = Instantiate(Resources.Load("UI/Prefabs/DamageUI")) as GameObject;//데미지UI 오브젝트생성
            damageUI.GetComponent<DamageUI>().SetDamage(gameObject, damage, color);
            hurt = true;
            currentHp -= damage;
            myRigidbody.AddForce(new Vector2(0, 5f), ForceMode2D.Impulse);
            StartCoroutine(HurtBlinkTimer());
            StartCoroutine(HurtKnockBackTimer(monPos));
        }
    }

    private void SetBoolMove(bool button)
    {
        switch (button)
        {
            case true:
                headAnimator.SetBool("move", true);
                bodyAnimator.SetBool("move", true);
                leftLegAnimator.SetBool("move", true);
                rightLegAnimator.SetBool("move", true);
                helmetAnimator.SetBool("move", true);
                shieldAnimator.SetBool("move", true);
                swordAnimator.SetBool("move", true);
                break;
            case false:
                headAnimator.SetBool("move", false);
                bodyAnimator.SetBool("move", false);
                leftLegAnimator.SetBool("move", false);
                rightLegAnimator.SetBool("move", false);
                helmetAnimator.SetBool("move", false);
                shieldAnimator.SetBool("move", false);
                swordAnimator.SetBool("move", false);
                break;
        }
    }

    private void SetTriggerJumpStart(bool button)
    {
        switch (button)
        {
            case true:
                headAnimator.SetTrigger("jump");
                bodyAnimator.SetTrigger("jump");
                leftLegAnimator.SetTrigger("jump");
                rightLegAnimator.SetTrigger("jump");
                helmetAnimator.SetTrigger("jump");
                shieldAnimator.SetTrigger("jump");
                swordAnimator.SetTrigger("jump");
                break;
            case false:
                headAnimator.ResetTrigger("jump");
                bodyAnimator.ResetTrigger("jump");
                leftLegAnimator.ResetTrigger("jump");
                rightLegAnimator.ResetTrigger("jump");
                helmetAnimator.ResetTrigger("jump");
                shieldAnimator.ResetTrigger("jump");
                swordAnimator.ResetTrigger("jump");
                break;
        }
    }

    private void SetBoolJumpEnd(bool button)
    {
        switch (button)
        {
            case true:
                headAnimator.SetBool("jumpEnd", true);
                bodyAnimator.SetBool("jumpEnd", true);
                leftLegAnimator.SetBool("jumpEnd", true);
                rightLegAnimator.SetBool("jumpEnd", true);
                helmetAnimator.SetBool("jumpEnd", true);
                shieldAnimator.SetBool("jumpEnd", true);
                swordAnimator.SetBool("jumpEnd", true);
                break;
            case false:
                headAnimator.SetBool("jumpEnd", false);
                bodyAnimator.SetBool("jumpEnd", false);
                leftLegAnimator.SetBool("jumpEnd", false);
                rightLegAnimator.SetBool("jumpEnd", false);
                helmetAnimator.SetBool("jumpEnd", false);
                shieldAnimator.SetBool("jumpEnd", false);
                swordAnimator.SetBool("jumpEnd", false);
                break;
        }
    }

    private void SetTriggerAttack(bool button)
    {
        switch (button)
        {
            case true:
                headAnimator.SetTrigger("attack");
                bodyAnimator.SetTrigger("attack");
                leftLegAnimator.SetTrigger("attack");
                rightLegAnimator.SetTrigger("attack");
                helmetAnimator.SetTrigger("attack");
                shieldAnimator.SetTrigger("attack");
                swordAnimator.SetTrigger("attack");
                break;
            case false:
                headAnimator.ResetTrigger("attack");
                bodyAnimator.ResetTrigger("attack");
                leftLegAnimator.ResetTrigger("attack");
                rightLegAnimator.ResetTrigger("attack");
                helmetAnimator.ResetTrigger("attack");
                shieldAnimator.ResetTrigger("attack");
                swordAnimator.ResetTrigger("attack");
                break;
        }
    }

    IEnumerator JumpTimer()
    {
        SetTriggerJumpStart(true);
        SetBoolJumpEnd(false);
        yield return new WaitForSeconds(0.1f);
        myRigidbody.velocity = Vector2.up * jumpForce;
    }

    IEnumerator AttackCollider()
    {
        attackCollider.SetActive(true);
        yield return new WaitForSeconds(0.2f);
        attackCollider.SetActive(false);
    }
    
    IEnumerator HurtBlinkTimer()//피격시 투명도 코루틴 (1초)
    {
        for (int i = 0; i < 10; i++)
        {
            if (i % 2 == 0)
            {
                headSpriteRenderer.color = new Color32(255, 255, 255, 100);
                bodySpriteRenderer.color = new Color32(255, 255, 255, 100);
                leftSpriteRenderer.color = new Color32(255, 255, 255, 100);
                rightLegSpriteRenderer.color = new Color32(255, 255, 255, 100);
                helmetSpriteRenderer.color = new Color32(255, 255, 255, 100);
                shieldSpriteRenderer.color = new Color32(255, 255, 255, 100);
                swordSpriteRenderer.color = new Color32(255, 255, 255, 100);
            }
            else
            {
                headSpriteRenderer.color = new Color32(255, 255, 255, 255);
                bodySpriteRenderer.color = new Color32(255, 255, 255, 255);
                leftSpriteRenderer.color = new Color32(255, 255, 255, 255);
                rightLegSpriteRenderer.color = new Color32(255, 255, 255, 255);
                helmetSpriteRenderer.color = new Color32(255, 255, 255, 255);
                shieldSpriteRenderer.color = new Color32(255, 255, 255, 255);
                swordSpriteRenderer.color = new Color32(255, 255, 255, 255);
            }
            yield return new WaitForSeconds(0.1f);
        }
        hurt = false;
    }

    IEnumerator HurtKnockBackTimer(bool monPos)
    {
        for(int i = 0; i<1000; i++)
        {
            Vector3 pos = transform.position;
            switch (monPos)
            {
                case true:
                    facingLeft = false;
                    pos.x -= 0.1f;
                    break;
                case false:
                    facingLeft = true;
                    pos.x += 0.1f;
                    break;
            }
            transform.position = pos;
            if (isGrounded == true && i > 10) break;
            yield return new WaitForSeconds(0.001f);
            
        }
    }
}
