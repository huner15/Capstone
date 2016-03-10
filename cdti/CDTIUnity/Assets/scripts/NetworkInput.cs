using UnityEngine;
using System.Collections;
using System.Net.Sockets;
using System.Net;
using System;
using Example;
using System.Threading;
using CielaSpike;
using System.IO;

public class NetworkInput : MonoBehaviour {

    TcpListener server = null;
    NetworkStream stream;
    Thread mThread;
    private bool isRunning;



    public Sprite airTrafficDirectional, airTrafficNonDirectional, proximateTrafficDirectional, proximateTrafficNonDirectional, resolutionAdvisoryDirectional, trafficAdvisoryDirectional;
    public GameObject aircraftBuilder;
    private System.Collections.Generic.List<GameObject> aircraft = new System.Collections.Generic.List<GameObject>();
    private System.Collections.Generic.List<GameObject> aircraftHidden = new System.Collections.Generic.List<GameObject>();
    public GameObject circle;
    private string message = "";
    public int maxRange = 20;
    private CDTIReport lastReport = null;
    private Vector pos = new Vector();
    private GameObject plane;

    static System.IO.StreamWriter writer;

    public static void logger(String str)
    {
        print(str);
        try
        {
            if(writer == null)
            {
                if (!System.IO.File.Exists("log.txt"))
                {
                    System.IO.File.Create("log.txt");
                }

                writer = new System.IO.StreamWriter(System.IO.File.OpenWrite("log.txt"));
             }

             writer.WriteLine(str);
             writer.Flush();
        }
        catch(Exception)
        {
            print("write failled");
        }
    }




    void OnGUI()
    {
        int h = Screen.height;
        int w = Screen.width;
        Console.Write("boom");
        GUI.Label(new Rect(w/1.7f, h/2, 20, 20), "" + (maxRange/4));
        GUI.Label(new Rect(w/1.52f, h/2, 20, 20), "" + (maxRange * 2 / 4));
        GUI.Label(new Rect(w/1.37f, h/2, 20, 20), "" + (maxRange * 3 / 4));
        GUI.Label(new Rect(w/1.26f, h/2, 20, 20), "" + (maxRange));
        GUI.Label(new Rect(w / 2, 0, 100, 20), message);
    }


    public void zoomIn()
    {
        if (maxRange > 4)
            maxRange -= 4;
        zoomCommon();
    }
    public void zoomOut()
    {

        maxRange += 4;
        zoomCommon();
    }
    private void zoomCommon()
    {
       
        if (lastReport != null)
        {
            intake(lastReport);
        }
    }



    // Use this for initialization
    void Start () {
        GameObject addCircles;

        addCircles = Instantiate(circle) as GameObject;
        addCircles.GetComponent<Transform>().localScale =new Vector3(2.64f, 2.64f, 1);
        addCircles.GetComponent<Transform>().position = new Vector3(0f, .14f, 0);
        addCircles = Instantiate(circle) as GameObject;
        addCircles.GetComponent<Transform>().localScale = new Vector3(1.98f,1.98f, 1);
        addCircles.GetComponent<Transform>().position = new Vector3(0f, .14f, 0);
        addCircles = Instantiate(circle) as GameObject;
        addCircles.GetComponent<Transform>().localScale = new Vector3(1.33f, 1.33f, 1);
        addCircles.GetComponent<Transform>().position = new Vector3(0f, .14f, 0);
        addCircles = Instantiate(circle) as GameObject;
        addCircles.GetComponent<Transform>().localScale = new Vector3(.67f, .67f, 1);
        addCircles.GetComponent<Transform>().position = new Vector3(0f, .14f, 0);


        plane = Instantiate(aircraftBuilder) as GameObject;
        pos.X = 0;
        pos.Y = -20;
        pos.Z = 0;
        


        isRunning = true;
        this.StartCoroutineAsync(connect());

        //ThreadStart ts = new ThreadStart(connect);
       // mThread = new Thread(ts);
        //mThread.Start();
        print("Thread done...");
        

        /*
        Int32 port = 13000;
        IPAddress localAddr = IPAddress.Parse("127.0.0.1");

        // TcpListener server = new TcpListener(port);
        server = new TcpListener(localAddr, port);
        
        // Start listening for client requests.
        server.Start();

        Console.WriteLine("waiting fr a connection... ");

        TcpClient client = server.AcceptTcpClient();
        Console.WriteLine("Connected");

        stream = client.GetStream();
        */

    }

    public void stopListening()
    {
        isRunning = false;
    }


    IEnumerator connect()
    {
       
        server = new TcpListener(IPAddress.Parse("127.0.0.1"), 13000);
        server.Start();
        logger("server Start");
        while (isRunning)
        {
                // check if new connections are pending, if not, be nice and sleep 100ms
            if (!server.Pending())
            {
                Thread.Sleep(100);
            }
            else
            {
                File.Delete("temp.txt");
              
                TcpClient client = server.AcceptTcpClient();
                logger("connection established");
          
                NetworkStream ns = client.GetStream();
                const int bufSize = 0x1000;
                byte[] buf = new byte[bufSize];
                bool rep = false;
                Example.CDTIReport report = null;
               // MemoryStream ms = new MemoryStream();
                Thread.Sleep(400);
                long totalBytes = 0;
                int bytesRead = 0;
                while((bytesRead = ns.Read(buf,0,bufSize)) > 0)
                {
                    File.Delete("temp.txt");
                    FileStream file = new FileStream("temp.txt", FileMode.Create);
                    file.Write(buf, 0, bytesRead);
                   // ms.Write(buf, 0, bytesRead);
                    totalBytes += bytesRead;
                    file.Close();
                    print(bytesRead);
                    
                    FileStream fs = new FileStream("temp.txt", FileMode.Open);
                    try
                    {
                       
                        report = Example.CDTIReport.Deserialize(fs);
                        fs.Close();
                        logger("" +report.Planes.Count);
                        logger("" +report.Ownship);
                        logger("" +report.Timestamp);
                        logger(report.AdvisoryMessage);
                        rep = true;
                        lastReport = report;
                        
                    }
                    catch(Exception)
                    {
                        fs.Close();
                    }
                    if(rep)
                    {
                        yield return Ninja.JumpToUnity;
                        intake(report);
                        // intake(CDTIReport.Deserialize(ns));
                        yield return Ninja.JumpBack;
                        rep = false;
                    }
                }
                
                client.Close();
            }
        }

        server.Stop();
        yield return null;
    }
	
	// Update is called once per frame
	void Update () {

        //try to read in the client info here.
        /*if(stream.DataAvailable)
        {
            intake(CDTIReport.Deserialize(stream));
        }*/
	}

    private void  intake(CDTIReport report)
    {
        logger("at intake");

        clearPlanes();

        foreach (CDTIPlane plane in report.Planes)
        {
            AddToScreen(plane);
        }
        AddToScreen(report.Ownship);

		logger("end intake");
    }

    private void AddToScreen(CDTIPlane plane)
    {
        GameObject toAdd;
        if (aircraftHidden.Count > 0)
        {
            toAdd = aircraftHidden[0];
            aircraftHidden.Remove(toAdd);
        }
        else
        {
            toAdd = Instantiate(aircraftBuilder) as GameObject;
        }


        toAdd.GetComponent<SpriteRenderer>().sprite = getCorrectSprite(plane);
        toAdd.GetComponent<Transform>().position = figurePositon(plane);
        toAdd.GetComponent<Transform>().rotation = figureRotation(plane);
        if(plane.Position.X != 0 || plane.Position.Y != 0 || plane.Position.Z != 0)
        {
            toAdd.GetComponent<Aircraft>().addText(plane);
        }
        

		logger("added to screed " + plane.Id);
        aircraft.Add(toAdd);
        //throw new NotImplementedException();
    }

    private void setUpText(GameObject toAdd, CDTIPlane plane)
    {
        
        throw new NotImplementedException();
    }

    private Quaternion figureRotation(CDTIPlane plane)
    {
        try
        {
            float theta = 0;

            theta = (float)(Math.Atan2(plane.Velocity.Y, plane.Velocity.X) * 180 / 3.14 - 90);
            print(theta);
            if (plane.Velocity.X == 0 && plane.Velocity.Y == 0)
            {
                theta = 0;
            }
            return Quaternion.AngleAxis(theta, new Vector3(0, 0, 1));
        }
        catch (Exception)
        {
            return Quaternion.AngleAxis(0, new Vector3(0, 0, 1));
        }


        
    }

    private Vector3 figurePositon(CDTIPlane plane)
    {
        
        Vector3 positon;

        if (plane == null)
        {
            positon.x = pos.X / maxRange * 5;
            positon.y = pos.Y / maxRange * 5;
            positon.z = 0;
            
            return positon;
        }


        positon.x = plane.Position.X/maxRange*5;
        positon.y = plane.Position.Y/maxRange*5;
        positon.z = 0;
       
        //add writing for the elevation later
        return positon;
       // throw new NotImplementedException();
    }

    private Sprite getCorrectSprite(CDTIPlane plane)
    {
        if(plane == null)
        {
            return airTrafficDirectional;
        }

        switch (plane.severity) {
            case (CDTIPlane.Severity.PROXIMATE):
                if (plane.Velocity.X == 0 && plane.Velocity.Y == 0)
                {
                    return proximateTrafficNonDirectional;
                }
                else
                    return proximateTrafficDirectional;
            case (CDTIPlane.Severity.TRAFFIC):
                return trafficAdvisoryDirectional;
            case (CDTIPlane.Severity.RESOLUTION):
                return resolutionAdvisoryDirectional;

            default:
                if (plane.Velocity.X == 0 && plane.Velocity.Y == 0)
                {
                    return airTrafficNonDirectional;
                }
                else
                    return airTrafficDirectional;
                
        }
            
                

    }

    private void clearPlanes()
    {
        foreach(GameObject plane in aircraft)
        {
            plane.GetComponent<SpriteRenderer>().sprite = null;
            aircraftHidden.Add(plane);
            plane.GetComponent<Aircraft>().clear();
           // Destroy(plane);
            
        }
        aircraft.Clear();


       // throw new NotImplementedException();
    }

    void OnApplicationQuit()
    {
        // stop listening thread
        stopListening();
        // wait fpr listening thread to terminate (max. 500ms)
      //  mThread.Join(500);
    }
}
