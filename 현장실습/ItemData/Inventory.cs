using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class Inventory : MonoBehaviour
{
    public static Inventory instance = null;
    GameObject inventory_window = null;
    GameObject status_window = null;
    const int inventory_max = 19;
    int current_count;

    public Sprite defaultImage = null;
    bool window_show;
    public bool isSHOP;
    public List<GameObject> slots;
    public GameObject equipment_Head = null;
    public GameObject equipment_weapon = null;
    public GameObject equipment_Armor = null;
    public int equipment_count;
    public int consume_count;
    public int etc_count;


    //클래스를 하나만 두고 초기화하는 함수
    void Awake()
    {
        if (instance == null)
            instance = this;
        else if (instance != this)
            Destroy(gameObject);

        DontDestroyOnLoad(gameObject);
        //UI 싱글톤 찾아보기

        window_show = false;
        isSHOP = false;
        inventory_window = GameObject.Find("item_bg");
        status_window = GameObject.Find("status_bg");
        slots = new List<GameObject>();
        equipment_Head = GameObject.Find("equipment_Head");
        equipment_weapon = GameObject.Find("equipment_weapon");
        equipment_Armor = GameObject.Find("equipment_Armor");

        foreach (GameObject slot in GameObject.FindGameObjectsWithTag("Inventory_slot"))
            slots.Add(slot);
        defaultImage = slots[0].GetComponent<Image>().sprite;
        current_count = 0;
        equipment_count = 0;
        consume_count = 0;
        etc_count = 0;
        inventory_window.SetActive(false);
        status_window.SetActive(false);
        

    }

    // i 버튼을 이용해 아이템창을 여는 함수
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.I)) {
            if (window_show == false)
            {
                inventory_window.SetActive(true);
                status_window.SetActive(true);
                window_show = true;
            }
            else
            {
                inventory_window.SetActive(false);
                status_window.SetActive(false);
                window_show = false;
            }
        }

            if (Input.GetKeyDown(KeyCode.Z) && equipment_count > 0)
            { pop_list(equipment_count);
                equipment_count--;
            }
            if (Input.GetKeyDown(KeyCode.X) && consume_count > 0)
            { pop_list(equipment_count + consume_count);
                consume_count--;
            }
            if (Input.GetKeyDown(KeyCode.C) && etc_count > 0)
            { pop_list(equipment_count + consume_count + etc_count);
                etc_count--;
            }

        }

    //새로운 아이템을 슬롯에 넣기전에 하나씩 밀어서 공간을 확보하는 함수
    void push_list(int start)
    {
        Item to;
        for (int pos = current_count; pos >= start; pos--)
        {
            if (pos + 1 < 20)
            {
                to = slots[pos + 1].GetComponent<Item>();
                clone(slots[pos].GetComponent<Item>(), to);
                Debug.Log("클론이 문젠가?");
                slots[pos + 1].GetComponent<Image>().sprite = (to.image == null ? defaultImage : to.image);
                slots[pos + 1].GetComponentInChildren<Text>().text = (to.property.count > 0 ? " "+ to.property.count : " ");
            }
        }

        current_count++;
    }

    //아이템을 슬롯에서 빼고나서 하나씩 끌어서 공간을 확보하는 함수
    public void pop_list(int start)
    {
        Debug.Log("pop 실행");
        Item to;
        int pos;
        start--;

        for (pos = start; pos <= current_count-2; pos++)
        {
            to = slots[pos].GetComponent<Item>();
            clone(slots[pos + 1].GetComponent<Item>(), slots[pos].GetComponent<Item>());
            slots[pos].GetComponent<Image>().sprite = to.image;
            slots[pos].GetComponentInChildren<Text>().text = (to.property.count > 0 ? " " + to.property.count : " "); ;
        }

        Item LastSlot = slots[pos].GetComponent<Item>();
        LastSlot.code = 0;
        LastSlot.image = null;
        LastSlot.property.name = null;
        LastSlot.property.info = null;
        LastSlot.property.count = 0;
        LastSlot.property.buyPrice = 0;
        LastSlot.property.sellPrice = 0;
        LastSlot.property.tag = null;
        LastSlot.property.part = null;
        LastSlot.GetComponent<Image>().sprite = defaultImage;
        LastSlot.GetComponentInChildren<Text>().text = " ";

        current_count--;
    }

    //새로운 아이템을 추가하기 위한 함수
    public void Add(GameObject item)
    {
        Debug.Log(item.name);
        if (current_count >= 20)
            return;

        Item from, to;
        int start, end;
        switch (item.GetComponent<Item>().property.tag)
        {
            case "equipment":
                Debug.Log("비교까지 되는지 확인");
                push_list(equipment_count);
                Debug.Log("푸쉬까지 되는지 확인");
                to = slots[equipment_count].GetComponent<Item>();
                clone(item.GetComponent<Item>(), to);

                slots[equipment_count].GetComponent<Image>().sprite = to.image;
                slots[equipment_count].GetComponentInChildren<Text>().text = (to.property.count > 0 ? " " + to.property.count : " "); ;

                equipment_count++;
                break;

            case "consume":
                start = equipment_count;
                end = equipment_count + consume_count;
                for (int i = start; i < end; i++)
                    if (item.GetComponent<Item>().code == slots[i].GetComponent<Item>().code)
                    {
                        slots[i].GetComponent<Item>().property.count += item.GetComponent<Item>().property.count;
                        slots[i].GetComponentInChildren<Text>().text = " " + slots[i].GetComponent<Item>().property.count;
                        Debug.Log("추가");
                        return;
                    }
                push_list(equipment_count + consume_count);
                from = item.GetComponent<Item>();
                to = slots[equipment_count + consume_count].GetComponent<Item>();
                clone(item.GetComponent<Item>(), to);

                slots[equipment_count + consume_count].GetComponent<Image>().sprite = to.image;
                slots[equipment_count + consume_count].GetComponentInChildren<Text>().text = (to.property.count > 0 ? " " + to.property.count : " "); ;

                consume_count++;
                break;

            case "etc":
                start = equipment_count + consume_count;
                end = equipment_count + consume_count + etc_count;
                for (int i = start; i < end; i++)
                    if (item.GetComponent<Item>().code == slots[i].GetComponent<Item>().code)
                    {
                        slots[i].GetComponent<Item>().property.count += item.GetComponent<Item>().property.count;
                        slots[i].GetComponentInChildren<Text>().text = " " + slots[i].GetComponent<Item>().property.count;
                        return;
                    }
                push_list(equipment_count + consume_count + etc_count);
                to = slots[equipment_count + consume_count + etc_count].GetComponent<Item>();
                clone(item.GetComponent<Item>(), to);

                slots[equipment_count + consume_count + etc_count].GetComponent<Image>().sprite = to.image;
                slots[equipment_count + consume_count + etc_count].GetComponentInChildren<Text>().text = (to.property.count > 0 ? " " + to.property.count : " "); ;

                etc_count++;
                break;

        }
        
    }

    public void clone(Item from, Item to)
    {
        Debug.Log(copy(from.property.tag));
        to.code = from.code;
        to.image = from.image;
        to.property.name = copy(from.property.name);
        to.property.info = copy(from.property.info);
        to.property.count = from.property.count;
        to.property.buyPrice = from.property.buyPrice;
        to.property.sellPrice = from.property.sellPrice;
        to.property.tag = copy(from.property.tag);
        to.property.part = copy(from.property.part);
}

    string copy(string Word)
    {
        if (Word != null)
            return string.Copy(Word);
        else
            return null;
    }










}