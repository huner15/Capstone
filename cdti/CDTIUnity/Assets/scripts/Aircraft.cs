using UnityEngine;
using System.Collections;
using Example;

public class Aircraft : MonoBehaviour {

    private GameObject text ;
	// Use this for initialization
	void Start () {
       

	}
	
	// Update is called once per frame
	void Update () {
	
	}

    public void addText(CDTIPlane plane)
    {
        text = new GameObject();
        text.AddComponent<TextMesh>();
        text.transform.localScale = new Vector3(.025f, .025f, 1);
        text.transform.SetParent(transform);
        Instantiate(text);
        text.GetComponent<TextMesh>().fontSize = 120;
        text.GetComponent<TextMesh>().fontStyle = FontStyle.Normal;
        text.GetComponent<TextMesh>().text = plane.Id + "\n" + plane.Position.Z;
        
        text.transform.position = transform.position + new Vector3(.2f, .2f, 0);
    }

    public void clear()
    {
        print("destroyed");
        Destroy(text);
    }


}
