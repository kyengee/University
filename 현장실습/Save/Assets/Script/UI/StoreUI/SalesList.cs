﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SalesList : MonoBehaviour
{
    [SerializeField]
    public ItemManager itemManager = ItemManager.instance;

    //[SerializeField]
    public List<ItemData> salesList = new List<ItemData>();

    public string storeTitleText;

    //private int iItemTag;

    void Awake()
    {
        storeTitleText = GameObject.Find("Canvas/storeui/title/titleText").GetComponent<Text>().text;
        ItemTag(storeTitleText);
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void ItemTag(string strTag)
    {
        if("장비" == strTag)
        {
            GetWeapons();
        }

        else if("소비" == strTag)
        {
        }
    }

    private void GetWeapons()
    {
        //List<ItemData> item = new List<ItemData>();

        // 모자
        int num = 3;
        for (int i = 0; i < num; ++i)
        {
            salesList.Add(itemManager.GetItem(110, num)[i]);
        }

        // 롱소드
        num = 3;
        for (int i = 0; i < num; ++i)
        {
            salesList.Add(itemManager.GetItem(140, num)[i]);
        }

        // 대검
        num = 3;
        for (int i = 0; i < num; ++i)
        {
            salesList.Add(itemManager.GetItem(141, num)[i]);
        }

        // 창
        //num = 3;
        //for (int i = 0; i < num; ++i)
        //{
        //    salesList.Add(itemManager.GetItem(142, num)[i]);
        //}
    }

    public List<ItemData>   GetSalesList()
    {
        if (salesList.Count == 0)
            return new List<ItemData>();

        else
            return salesList;
    }
}
