using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;


namespace M6_CSS_VR {


	public class MySceneManager : MonoBehaviour {

		// Use this for initialization
		Dictionary<string, Scene> SceneMaps;

		[SerializeField]
		Dictionary<string, Transform> ChildTransformMaps;

		void Start () {

			SceneMaps = new Dictionary<string, Scene>();
			ChildTransformMaps = new Dictionary<string, Transform>();

			Debug.Log ("SceneManagement::sceneCount: " + SceneManager.sceneCount);
			Debug.Log ("SceneManagement::sceneCountInBuildSettings: " + SceneManager.sceneCountInBuildSettings);

			SceneManager.sceneLoaded += OnSceneLoaded;

			foreach (Transform c in transform) {

				string name = c.name;
				string[] nameSplits = c.name.Split(new string[] {" | "}, System.StringSplitOptions.None);

				if (nameSplits.Length > 1)  // Scene without timeCode
				{
					name = nameSplits [1];
					c.gameObject.SetActive (false);					
				}
				ChildTransformMaps.Add (name, c);

				SceneManager.LoadSceneAsync (name, LoadSceneMode.Additive);
			}
				
		}
		// called second
		void OnSceneLoaded(Scene scene, LoadSceneMode mode)
		{
			//Debug.Log("OnSceneLoaded: " + scene.name);
			//Debug.Log(mode);

			SceneMaps.Add (scene.name, scene);

			GameObject[] GOes = scene.GetRootGameObjects ();
			Transform _p = ChildTransformMaps[scene.name];
			if(_p != null){
				foreach(GameObject go in GOes){
					go.transform.parent = _p;
				}
			}

		}


		Rect rect = new Rect(10,10, 180, 300);
		void OnGUI(){

			GUILayout.BeginArea (rect);

			GUILayout.TextField (SceneManager.GetActiveScene ().name);

			GUILayout.EndArea();

		}

	}
}