﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

public class ItemManager : MonoBehaviour
{
    public static ItemManager instance = null;

    public static ItemManager GetInstance()
    {
        if (instance == null)
            instance = new ItemManager();

        return instance;
    }
    public TextAsset csvFile;
    protected string[] data;
    protected string[] stringList;
    protected string text;

    [SerializeField]
    private List<Item> itemList = new List<Item>();

    private StringReader reader;
    private string strLine;
    private int lineCount;

    void Awake()
    {
        instance = this;

        // 문자 구분을 위한 변수 선언
        text = csvFile.text;
        stringList = text.Split('\n');
    }

    // Start is called before the first frame update
    void Start()
    {
        reader = new StringReader(csvFile.text);
        strLine = reader.ReadLine();

        int i = 0;
        while (strLine != null)
        {
            strLine = reader.ReadLine();
            i++;

        }

        // 최상단은 컬럼명이므로 카운트에서 제외
        lineCount = i - 1;

        for (int j = 1; j <= lineCount; j++)
        {
            Item item = new Item();

            item.code = getCode(j);
            item.name = getName(j);
            item.maxcount = getMaxcount(j);
            item.sellprice = getSellprice(j);
            item.buyprice= getBuyprice(j);
            item.option1= getOpt1(j);
            item.option1_1= getOpt1_1(j);
            item.option2 = getOpt2(j);
            item.option2_1= getOpt2_1(j);
            
            itemList.Add(item);
        }
    }

    // Update is called once per frame
    void Update()
    {
       // Debug.Log(GetOption1(11001));
    }

    // csv에서 로드할 때 쓰는 함수들
    int getCode(int index)
    {
        data = stringList[index].Split(',');
        return int.Parse(data[0]);
    }

    string getName(int index)
    {
        data = stringList[index].Split(',');
        return data[1];
    }

    int getMaxcount(int index)
    {
        data = stringList[index].Split(',');
        return int.Parse(data[2]);
    }

    int getSellprice(int index)
    {
        data = stringList[index].Split(',');
        return int.Parse(data[3]);
    }

    int getBuyprice(int index)
    {
        data = stringList[index].Split(',');
        return int.Parse(data[4]);
    }

    string getOpt1(int index)
    {
        data = stringList[index].Split(',');
        return data[5];
    }

    int getOpt1_1(int index)
    {
        data = stringList[index].Split(',');
        return int.Parse(data[6]);
    }

    string getOpt2(int index)
    {
        data = stringList[index].Split(',');
        return data[7];
    }

    int getOpt2_1(int index)
    {
        data = stringList[index].Split(',');
        return int.Parse(data[8]);
    }


    // 코드번호 -> 아이템의 정보
    public Item GetItemInfo(int code)
    {
        for(int i = 0; i < itemList.Count; ++i)
        {
            if (itemList[i].code == code)
            {
                return itemList[i];
            }
        }
        
        return null;
    }


    // 코드번호 -> 아이템 이름
    public string GetItemName(int code)
    {
        for (int i = 0; i < itemList.Count; ++i)
        {
            if (itemList[i].code == code)
            {
                return itemList[i].name;
            }
        }

        return null;
    }

    // 코드번호 -> 옵션1 (ex. 공격력 10), 찾는게 없으면 null 리턴
    public string GetOption1(int code)
    {
        for (int i = 0; i < itemList.Count; ++i)
        {
            if (itemList[i].code == code)
            {
                return itemList[i].option1 + " " + itemList[i].option1_1.ToString();
            }
        }

        return null;
    }

    // 코드번호 -> 옵션1 (ex. 공격력 +10), 찾는게 없으면 null 리턴
    public string GetOption1Sign(int code)
    {
        for (int i = 0; i < itemList.Count; ++i)
        {
            if (itemList[i].code == code)
            {
                if(itemList[i].option1_1 >= 0)
                    return itemList[i].option1 + " +" + itemList[i].option1_1.ToString();

                else
                    return itemList[i].option1 + " -" + itemList[i].option1_1.ToString();

            }
        }

        return null;
    }

    // 코드번호 -> 옵션2 (ex. 공격력 10), 찾는게 없으면 null 리턴
    public string GetOption2(int code)
    {
        for (int i = 0; i < itemList.Count; ++i)
        {
            if (itemList[i].code == code)
            {
                return itemList[i].option2 + " " + itemList[i].option2_1.ToString();
            }
        }

        return null;
    }

    // 코드번호 -> 옵션1 (ex. 공격력 +10), 찾는게 없으면 null 리턴
    public string GetOption2Sign(int code)
    {
        for (int i = 0; i < itemList.Count; ++i)
        {
            if (itemList[i].code == code)
            {
                if (itemList[i].option2_1 >= 0)
                    return itemList[i].option2 + " +" + itemList[i].option2_1.ToString();

                else
                    return itemList[i].option2 + " -" + itemList[i].option2_1.ToString();

            }
        }

        return null;
    }

    // 코드번호 -> maxcount, 찾는게 없으면 -1 리턴
    public int GetMaxcount(int code)
    {
        for (int i = 0; i < itemList.Count; ++i)
        {
            if (itemList[i].code == code)
            {
                return itemList[i].maxcount;
            }
        }

        return -1;
    }

    // 아이템 이름 -> maxcount
    public int GetMaxcount(string name)
    {
        for (int i = 0; i < itemList.Count; ++i)
        {
            if (itemList[i].name == name)
            {
                return itemList[i].maxcount;
            }
        }

        return -1;
    }

    // 코드번호 min ~ max 범위까지 (ex. min = 0, max = 3 이면 0, 1, 2, 3 값 리턴)
    public List<Item> GetItems(int min, int max)
    {
        List<Item> items = new List<Item>();

        for(int i = 0; i < itemList.Count; ++i)
        {
            if (min <= itemList[i].code && itemList[i].code <= max)
            {
                Debug.Log(itemList[i].code);
                items.Add(itemList[i]);
            }
          
        }

        return items;
    }
}
