using System.Collections;
using System.Collections.Generic;
using UnityEngine;


namespace M6_CSS_VR {

	[System.Serializable]
	public class TimeCode
	{
		public int ss = int.MaxValue;
		public int t = int.MaxValue;
		public int endMs = int.MaxValue;
	}

	public class MyActiveManger : MonoBehaviour {

		[SerializeField]
		Dictionary<string, Transform> ChildTransformMaps;
		[SerializeField]
		Dictionary<string, TimeCode> TimeCodeMaps;

		float activeTime;

		// Use this for initialization
		void Start () {
			ChildTransformMaps = new Dictionary<string, Transform>();
			TimeCodeMaps = new Dictionary<string, TimeCode>();

			string prevChild="", currChild="";
			foreach (Transform c in transform) {

				string name = currChild = c.name;
				string[] nameSplits = c.name.Split(new string[] {" | "}, System.StringSplitOptions.None);

				if (nameSplits.Length > 1)  // Scene without timeCode
				{
					name = currChild = nameSplits [1];
					TimeCode tc = JsonUtility.FromJson<TimeCode> (nameSplits [0]);
					TimeCodeMaps.Add (
						name, 
						tc
					);

					if (tc.ss == -1 && prevChild != "") 
					{
						tc.ss = TimeCodeMaps [prevChild].endMs;
					}

					if (tc.t >= 0) {
						TimeCodeMaps [name].endMs = tc.ss +tc.t;
					}
					c.gameObject.SetActive (false);
				}

				prevChild = currChild;
				ChildTransformMaps.Add (name, c);
			}

			activeTime = Time.time;
		}

		Rect rect = new Rect(10,10, 300, 300);

		void OnEnable(){
			activeTime = Time.time;
		}

		// Update is called once per frame
		void Update () 
		{
			int timeMs = (int)( (Time.time - activeTime) * 1000f);
			List<string> deleteList = new List<string> ();

			foreach( KeyValuePair<string, TimeCode> pair in TimeCodeMaps )
			{
				string name = pair.Key;
				TimeCode tc = pair.Value;
				GameObject childGO = ChildTransformMaps [name].gameObject;

				if (timeMs >= tc.ss && timeMs < tc.endMs && !childGO.activeInHierarchy) 
				{
					childGO.SetActive (true);
				}
				else if(timeMs >= tc.endMs && childGO.activeInHierarchy)
				{
					childGO.SetActive (false);
					deleteList.Add (name);
				}
			}	

			foreach (string key in deleteList) {
				TimeCodeMaps.Remove (key);
			}
		}
	}
}