using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemManager : MonoBehaviour
{
    public static ItemManager instance = null;
    public List<Item>[][] itemList = null;
    Dictionary<string, string> tag = null;
    Dictionary<string, string> part = null;
    
    private void Awake()
    {
        if (instance == null)
            instance = this;
        else if (instance != this)
            Destroy(gameObject);
        DontDestroyOnLoad(gameObject);

        itemList = new List<Item>[3][]; // 3개의 tag 생성

        for (int i = 0; i < 3; i++){
            itemList[i] = new List<Item>[5]; // 각 tag마다 5개의 type 생성
            for (int j = 0; j < 5; j++)
                itemList[i][j] = new List<Item>(); // 각 type 마다 리스트 생성
        }

        itemList[1][2].Add(new Item());
        tag = new Dictionary<string, string>();
        part = new Dictionary<string, string>();

        tag["1"] = "장비"; tag["2"] = "소비"; tag["3"] = "기타";
        part["11"] = "무기"; part["12"] = "모자"; part["13"] = "방패"; part["14"] = "신발";
        part["21"] = "즉시물약"; part["22"] = "지속물약"; part["23"] = "버프물약";
        part["31"] = "재료"; part["32"] = "퀘스트";

        //테스트코드
        Debug.Log(GetItemInfo("1112", "tag"));
        Debug.Log(GetItemInfo("1124", "part"));
        Debug.Log(GetItemInfo("3227", "tag"));
        Debug.Log(GetItemInfo("3222", "part"));
        Debug.Log(itemList[1][2][0].code);
        Debug.Log(getItem("12000").code);
        Item ins = new Item();
        ins.code = int.Parse("5");
        Debug.Log(ins.code);

    }

    string GetItemInfo(string num, string index)
    {
        switch (index){
            case "tag":
                return tag[num.Substring(0, 1)];
            case "part":
                return part[num.Substring(0, 2)];
        }
        return "";
    }

    Item getItem(string code)
    {
        return itemList[int.Parse(code.Substring(0, 1))][int.Parse(code.Substring(1, 1))][int.Parse(code.Substring(2, 2))];
    }
}
