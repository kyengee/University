using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Wall : MonoBehaviour
{
    public Sprite dmgSprite;
    public int hp = 4;
    public AudioClip chapSound1;
    public AudioClip chapSound2;

    private SpriteRenderer spriteRenderer;

    void Awake()
    {
        spriteRenderer = GetComponent<SpriteRenderer>();
    }

    public void DamageWall (int loss)
    {
        SoundManager.instance.RandomizeSfx(chapSound1, chapSound2);
        spriteRenderer.sprite = dmgSprite;
        hp -= loss;

        if (hp <= 0)
            gameObject.SetActive(false);
    }

}
