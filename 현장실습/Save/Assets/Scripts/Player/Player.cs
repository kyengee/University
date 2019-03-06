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
    private bool hurt = false;

    //stat
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
        //Debug.Log(currentHp);
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
        if (horizontal < 0 && !facingLeft || horizontal > 0 && facingLeft)
        {
            facingLeft = !facingLeft;
            Vector3 theScale = transform.localScale;
            theScale.x *= -1;
            transform.localScale = theScale;
        }
    }

    public void Hurt(bool monPos, int damage)
    {
        if (!hurt)
        {
            hurt = true;
            currentHp -= damage;
            Vector3 pos = transform.position;
            if(monPos)
                pos.x -= 1f;
            else
                pos.x += 1f;
            transform.position = pos;
            StartCoroutine(HurtTimer());
            
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

    IEnumerator HurtTimer()
    {
        headSpriteRenderer.color = new Color(headSpriteRenderer.color.r, headSpriteRenderer.color.g, headSpriteRenderer.color.b, headSpriteRenderer.color.a / 2);
        bodySpriteRenderer.color = new Color(bodySpriteRenderer.color.r, bodySpriteRenderer.color.g, bodySpriteRenderer.color.b, bodySpriteRenderer.color.a / 2);
        leftSpriteRenderer.color = new Color(leftSpriteRenderer.color.r, leftSpriteRenderer.color.g, leftSpriteRenderer.color.b, leftSpriteRenderer.color.a / 2);
        rightLegSpriteRenderer.color = new Color(rightLegSpriteRenderer.color.r, rightLegSpriteRenderer.color.g, rightLegSpriteRenderer.color.b, rightLegSpriteRenderer.color.a / 2);
        helmetSpriteRenderer.color = new Color(helmetSpriteRenderer.color.r, helmetSpriteRenderer.color.g, helmetSpriteRenderer.color.b, helmetSpriteRenderer.color.a / 2);
        shieldSpriteRenderer.color = new Color(shieldSpriteRenderer.color.r, shieldSpriteRenderer.color.g, shieldSpriteRenderer.color.b, shieldSpriteRenderer.color.a / 2);
        swordSpriteRenderer.color = new Color(swordSpriteRenderer.color.r, swordSpriteRenderer.color.g, swordSpriteRenderer.color.b, swordSpriteRenderer.color.a / 2);
        yield return new WaitForSeconds(0.1f);
        headSpriteRenderer.color = new Color(headSpriteRenderer.color.r, headSpriteRenderer.color.g, headSpriteRenderer.color.b, headSpriteRenderer.color.a * 2);
        bodySpriteRenderer.color = new Color(bodySpriteRenderer.color.r, bodySpriteRenderer.color.g, bodySpriteRenderer.color.b, bodySpriteRenderer.color.a * 2);
        leftSpriteRenderer.color = new Color(leftSpriteRenderer.color.r, leftSpriteRenderer.color.g, leftSpriteRenderer.color.b, leftSpriteRenderer.color.a * 2);
        rightLegSpriteRenderer.color = new Color(rightLegSpriteRenderer.color.r, rightLegSpriteRenderer.color.g, rightLegSpriteRenderer.color.b, rightLegSpriteRenderer.color.a * 2);
        helmetSpriteRenderer.color = new Color(helmetSpriteRenderer.color.r, helmetSpriteRenderer.color.g, helmetSpriteRenderer.color.b, helmetSpriteRenderer.color.a * 2);
        shieldSpriteRenderer.color = new Color(shieldSpriteRenderer.color.r, shieldSpriteRenderer.color.g, shieldSpriteRenderer.color.b, shieldSpriteRenderer.color.a * 2);
        swordSpriteRenderer.color = new Color(swordSpriteRenderer.color.r, swordSpriteRenderer.color.g, swordSpriteRenderer.color.b, swordSpriteRenderer.color.a * 2);
        yield return new WaitForSeconds(0.1f);
        headSpriteRenderer.color = new Color(headSpriteRenderer.color.r, headSpriteRenderer.color.g, headSpriteRenderer.color.b, headSpriteRenderer.color.a / 2);
        bodySpriteRenderer.color = new Color(bodySpriteRenderer.color.r, bodySpriteRenderer.color.g, bodySpriteRenderer.color.b, bodySpriteRenderer.color.a / 2);
        leftSpriteRenderer.color = new Color(leftSpriteRenderer.color.r, leftSpriteRenderer.color.g, leftSpriteRenderer.color.b, leftSpriteRenderer.color.a / 2);
        rightLegSpriteRenderer.color = new Color(rightLegSpriteRenderer.color.r, rightLegSpriteRenderer.color.g, rightLegSpriteRenderer.color.b, rightLegSpriteRenderer.color.a / 2);
        helmetSpriteRenderer.color = new Color(helmetSpriteRenderer.color.r, helmetSpriteRenderer.color.g, helmetSpriteRenderer.color.b, helmetSpriteRenderer.color.a / 2);
        shieldSpriteRenderer.color = new Color(shieldSpriteRenderer.color.r, shieldSpriteRenderer.color.g, shieldSpriteRenderer.color.b, shieldSpriteRenderer.color.a / 2);
        swordSpriteRenderer.color = new Color(swordSpriteRenderer.color.r, swordSpriteRenderer.color.g, swordSpriteRenderer.color.b, swordSpriteRenderer.color.a / 2);
        yield return new WaitForSeconds(0.1f);
        headSpriteRenderer.color = new Color(headSpriteRenderer.color.r, headSpriteRenderer.color.g, headSpriteRenderer.color.b, headSpriteRenderer.color.a * 2);
        bodySpriteRenderer.color = new Color(bodySpriteRenderer.color.r, bodySpriteRenderer.color.g, bodySpriteRenderer.color.b, bodySpriteRenderer.color.a * 2);
        leftSpriteRenderer.color = new Color(leftSpriteRenderer.color.r, leftSpriteRenderer.color.g, leftSpriteRenderer.color.b, leftSpriteRenderer.color.a * 2);
        rightLegSpriteRenderer.color = new Color(rightLegSpriteRenderer.color.r, rightLegSpriteRenderer.color.g, rightLegSpriteRenderer.color.b, rightLegSpriteRenderer.color.a * 2);
        helmetSpriteRenderer.color = new Color(helmetSpriteRenderer.color.r, helmetSpriteRenderer.color.g, helmetSpriteRenderer.color.b, helmetSpriteRenderer.color.a * 2);
        shieldSpriteRenderer.color = new Color(shieldSpriteRenderer.color.r, shieldSpriteRenderer.color.g, shieldSpriteRenderer.color.b, shieldSpriteRenderer.color.a * 2);
        swordSpriteRenderer.color = new Color(swordSpriteRenderer.color.r, swordSpriteRenderer.color.g, swordSpriteRenderer.color.b, swordSpriteRenderer.color.a * 2);
        yield return new WaitForSeconds(0.1f);
        headSpriteRenderer.color = new Color(headSpriteRenderer.color.r, headSpriteRenderer.color.g, headSpriteRenderer.color.b, headSpriteRenderer.color.a / 2);
        bodySpriteRenderer.color = new Color(bodySpriteRenderer.color.r, bodySpriteRenderer.color.g, bodySpriteRenderer.color.b, bodySpriteRenderer.color.a / 2);
        leftSpriteRenderer.color = new Color(leftSpriteRenderer.color.r, leftSpriteRenderer.color.g, leftSpriteRenderer.color.b, leftSpriteRenderer.color.a / 2);
        rightLegSpriteRenderer.color = new Color(rightLegSpriteRenderer.color.r, rightLegSpriteRenderer.color.g, rightLegSpriteRenderer.color.b, rightLegSpriteRenderer.color.a / 2);
        helmetSpriteRenderer.color = new Color(helmetSpriteRenderer.color.r, helmetSpriteRenderer.color.g, helmetSpriteRenderer.color.b, helmetSpriteRenderer.color.a / 2);
        shieldSpriteRenderer.color = new Color(shieldSpriteRenderer.color.r, shieldSpriteRenderer.color.g, shieldSpriteRenderer.color.b, shieldSpriteRenderer.color.a / 2);
        swordSpriteRenderer.color = new Color(swordSpriteRenderer.color.r, swordSpriteRenderer.color.g, swordSpriteRenderer.color.b, swordSpriteRenderer.color.a / 2);
        yield return new WaitForSeconds(0.1f);
        headSpriteRenderer.color = new Color(headSpriteRenderer.color.r, headSpriteRenderer.color.g, headSpriteRenderer.color.b, headSpriteRenderer.color.a * 2);
        bodySpriteRenderer.color = new Color(bodySpriteRenderer.color.r, bodySpriteRenderer.color.g, bodySpriteRenderer.color.b, bodySpriteRenderer.color.a * 2);
        leftSpriteRenderer.color = new Color(leftSpriteRenderer.color.r, leftSpriteRenderer.color.g, leftSpriteRenderer.color.b, leftSpriteRenderer.color.a * 2);
        rightLegSpriteRenderer.color = new Color(rightLegSpriteRenderer.color.r, rightLegSpriteRenderer.color.g, rightLegSpriteRenderer.color.b, rightLegSpriteRenderer.color.a * 2);
        helmetSpriteRenderer.color = new Color(helmetSpriteRenderer.color.r, helmetSpriteRenderer.color.g, helmetSpriteRenderer.color.b, helmetSpriteRenderer.color.a * 2);
        shieldSpriteRenderer.color = new Color(shieldSpriteRenderer.color.r, shieldSpriteRenderer.color.g, shieldSpriteRenderer.color.b, shieldSpriteRenderer.color.a * 2);
        swordSpriteRenderer.color = new Color(swordSpriteRenderer.color.r, swordSpriteRenderer.color.g, swordSpriteRenderer.color.b, swordSpriteRenderer.color.a * 2);
        yield return new WaitForSeconds(0.5f);
        hurt = false;
    }


    private void OnTriggerEnter2D(Collider2D other)
    {

        Inventory.instance.Add(other.gameObject.GetComponent<Item_string>().code);
    }
}
