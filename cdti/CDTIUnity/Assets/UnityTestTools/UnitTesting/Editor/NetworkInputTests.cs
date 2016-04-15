using NUnit.Framework;
using System.Collections;
using Example;
using UnityEngine;

public class NetworkInputTests {
    [Test]
    public void testPostion()
    {
        CDTIPlane plane = new CDTIPlane();
        plane.Position = new Vector(5, 5, 0);
        NetworkInput toTest = new NetworkInput();
        Assert.That(1.25 == toTest.figurePositon(plane).x, "got: " + toTest.figurePositon(plane).x);
        Assert.That(1.25== toTest.figurePositon(plane).y, "got: " + toTest.figurePositon(plane).y);
        toTest.zoomIn();
        Assert.That(1.5625 == toTest.figurePositon(plane).x, "got: " + toTest.figurePositon(plane).x);
        Assert.That(1.5625 == toTest.figurePositon(plane).y, "got: " + toTest.figurePositon(plane).y);
        toTest.zoomOut();
        toTest.zoomOut();
        Assert.That(1.041667 == toTest.figurePositon(plane).x, "got: " + toTest.figurePositon(plane).x);
        Assert.That(1.041667 == toTest.figurePositon(plane).y, "got: " + toTest.figurePositon(plane).y);
    }
    [Test]
    public void testRotation()
    {
        CDTIPlane plane = new CDTIPlane();
        plane.Velocity = new Vector(1, 0, 0);
        NetworkInput toTest = new NetworkInput();
        Assert.That(Quaternion.AngleAxis(-90, new Vector3(0, 0, 1)).Equals(toTest.figureRotation(plane)));
        plane.Velocity = new Vector(1, 1, 0);
        Assert.That(Quaternion.AngleAxis(-45, new Vector3(0, 0, 1)).Equals(toTest.figureRotation(plane)));
        plane.Velocity = new Vector(0, 1, 0);
        Assert.That(Quaternion.AngleAxis(0, new Vector3(0, 0, 1)).Equals(toTest.figureRotation(plane)));
        plane.Velocity = new Vector(-1, 1, 0);
        Assert.That(Quaternion.AngleAxis(45, new Vector3(0, 0, 1)).Equals(toTest.figureRotation(plane)));
        plane.Velocity = new Vector(-1, 0, 0);
        Assert.That(Quaternion.AngleAxis(90, new Vector3(0, 0, 1)).Equals(toTest.figureRotation(plane)));
        plane.Velocity = new Vector(-1, -1, 0);
        Assert.That(Quaternion.AngleAxis(135, new Vector3(0, 0, 1)).Equals(toTest.figureRotation(plane)));
        plane.Velocity = new Vector(0, -1, 0);
        Assert.That(Quaternion.AngleAxis(180, new Vector3(0, 0, 1)).Equals(toTest.figureRotation(plane)));
        plane.Velocity = new Vector(1, -1, 0);
        Assert.That(Quaternion.AngleAxis(225, new Vector3(0, 0, 1)).Equals(toTest.figureRotation(plane)));
    }



}
