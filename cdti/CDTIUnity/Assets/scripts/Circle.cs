using UnityEngine;
using System.Collections;

public class Circle : MonoBehaviour {
    private GameObject text = null;
    // Use this for initialization
    void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    public void updateText(int zoom)
    {
        if (text == null)
        {
            text = new GameObject();
            text.AddComponent<TextMesh>();
            text.transform.localScale = new Vector3(.2f, .2f, 1);
            text.transform.SetParent(transform);
            Instantiate(text);
            text.GetComponent<TextMesh>().fontSize = 20;
            text.GetComponent<TextMesh>().fontStyle = FontStyle.Normal;
            text.transform.localPosition = new Vector3(2f, 0f, 0);
        }
        text.GetComponent<TextMesh>().text = "" + zoom;
        
        
    }

}
