using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class player : MovingObject
{
    public int wallDamage = 1;
    public int pointsPerFood = 10;
    public int pointPerSoda = 20;
    public float restartLevelDelay = 1f;
    public Text foodText;
    public AudioClip movesound1;
    public AudioClip movesound2;
    public AudioClip eatsound1;
    public AudioClip eatsound2;
    public AudioClip drinksound1;
    public AudioClip drinksound2;
    public AudioClip gameOversound;



    private Animator animator;

    private int food;

    private Vector2 touchOrigin = -Vector2.one;



    // Start is called before the first frame update
    protected override void Start()
    {
        animator = GetComponent<Animator>();
        food = GameManager.instance.playerFoodPoints;
        foodText.text = "food : " + food;

        base.Start();
    }

    private void OnDisable()
    {
        GameManager.instance.playerFoodPoints = food;
    }

    // Update is called once per frame
    void Update()
    {
        if (!GameManager.instance.playersTurn) return;

        int horizontal = 0;
        int vertical = 0;

#if UNITY_EDITOR || UNITY_STANDALONE || UNITY_WEBPLAYER
        horizontal = (int)Input.GetAxisRaw("Horizontal");
        vertical = (int)Input.GetAxisRaw("Vertical");

        if (horizontal != 0)
            vertical = 0;

#else 
        if (Input.touchCount > 0)
        {
            Touch myTouch = Input.touches[0];

            if (myTouch.phase == TouchPhase.Began)
            {
                touchOrigin = myTouch.position;
            }
            else if (myTouch.phase == TouchPhase.Ended && touchOrigin.x >= 0)
            {
                Vector2 touchEnd = myTouch.position;
                float x = touchEnd.x - touchOrigin.x;
                float y = touchEnd.y - touchOrigin.y;
                touchOrigin.x = -1;
                if (Mathf.Abs(x) > Mathf.Abs(y))
                    horizontal = x > 0 ? 1 : -1;
                else
                    vertical = y > 0 ? 1 : -1;
            }
        }
#endif

        if (horizontal != 0 || vertical != 0)
            AttempMove<Wall>(horizontal, vertical);
    }

    protected override void AttempMove<T>(int xDir, int yDir)
    {
        food--;
        foodText.text = "food : " + food;

        base.AttempMove<T>(xDir, yDir);

        RaycastHit2D hit;

        if (Move(xDir, yDir, out hit))
        {
            SoundManager.instance.RandomizeSfx(movesound1, movesound2);
        }

        CheckIfGameOver();

        GameManager.instance.playersTurn = false;
    }

    private void OnTriggerEnter2D(Collider2D other)
    {
        if (other.tag == "Exit")
        {
            Invoke("Restart", restartLevelDelay);
            enabled = false;
        }
        else if (other.tag == "Food")
        {
            food += pointsPerFood;
            foodText.text = "+" + pointsPerFood + "food : " + food;
            SoundManager.instance.RandomizeSfx(eatsound1, eatsound2);
            other.gameObject.SetActive(false);
        }
        else if (other.tag == "Soda")
        {
            food += pointPerSoda;
            foodText.text = "+" + pointPerSoda + "food : " + food;
            SoundManager.instance.RandomizeSfx(drinksound1, drinksound2);
            other.gameObject.SetActive(false);
        }
        else if (other.tag == "consume" || other.tag == "etc" || other.tag == "equipment")
            Inventory.instance.Add(other.gameObject.GetComponent<Item_string>().code);
    }


    protected override void OnCantMove<T>(T component)
    {
        Wall hitWall = component as Wall;
        hitWall.DamageWall(wallDamage);
        animator.SetTrigger("PlayerChap");
    }

    private void Restart()
    {
        Application.LoadLevel(Application.loadedLevel);
    }

    public void LoseFood(int loss)
    {
        animator.SetTrigger("PlayerHit");
        food -= loss;
        foodText.text = "-" + loss + "food : " + food;
        CheckIfGameOver();
    }

    private void CheckIfGameOver()
    {
        if (food <= 0)
        {
            SoundManager.instance.PlaySingle(gameOversound);
            SoundManager.instance.musicSource.Stop();
            GameManager.instance.GameOver();
        }
    }
}
