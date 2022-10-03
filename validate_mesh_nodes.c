+#define GETT_MESH_NODE_ALLOWED 5
 //validating mesh nodes
+
 char *validate_mesh_nodes(const char *key, const char *val){
-    int l = strlen(val); //11:22:33:44:55:66,22:ee:ff:gg:ll:aa
-    if (l < 1) {
+    char *value = malloc(GETT_MESH_NODE_ALLOWED * MAC_LEN);
+    //char *ret = NULL;
+    //char _value[GETT_MESH_NODE_ALLOWED * MAC_LEN] = {0}, *value = NULL; 
+    //value = &_value;
+
+    memset(value, 0, sizeof(GETT_MESH_NODE_ALLOWED * MAC_LEN));
+    strcpy(value, val);
+
+    int l = strlen(value); 
+    if (0 == l) {
+        free(value); value = NULL;
         return "add mac addresses";
-    }   
-    if (l < MAC_LEN) {
-        return "INVALID mac address";
-    }
-    if (l == MAC_LEN) {
-    //user input only one mac
-        if(validate_mac_addresses(val, l) < 0) {
-            return "INVALID MAC";
-        }
-        return "validated mesh nodes";
-    }
-    if (l > (MAC_LEN * 4) + 3) {
-        return "You can only add upto 4 mac addresses";
-    }
-    for (int i = MAC_LEN; i < (MAC_LEN + 1); i += (MAC_LEN + 1)) {
-        if (val[i] != ',') {
-            return "INVALID MACS";
-        }   
-    }
-    if(val[l-18] != ','){
-        return "INVALID MACS";
+    } 
+    if (l > (MAC_LEN * GETT_MESH_NODE_ALLOWED) + (GETT_MESH_NODE_ALLOWED - 1)) { //tot_maclen - delim (",")
+        free(value); value = NULL;
+        return "maximum 5 macs are allowed";
+    }
+    char *mac = NULL;
+    mac = strtok(value, ",");
+    while (mac != NULL) { 
+        int mlen = strlen(mac);
+        if (mlen != MAC_LEN) {
+            free(value); value = NULL;
+            return "invalid mac";
+        }  
+
+        for (int i = 2; i < (mlen - 2); i += 3) {
+            if (mac[i] == ':') {
+                continue;
+            } else {
+                free(value); value = NULL;
+                return "invalid mac fromat";
+            }
+        } 
+
+        for (int i = 0; i < mlen; i++) {
+            if ((mac[i] >= '0' && mac[i] <= '9') || (mac[i] >= 'a' && mac[i] <= 'f') || (mac[i] >= 'A' && mac[i] <= 'F') || (mac[i] == ':')) {
+                continue;
+            } else {
+                ret = "invalid mac chars";
+                goto bailout;
+                free(value); value = NULL;
+                return "invalid MACS";
+            } 
+        } 
+        mac = strtok(NULL, ",");
     }
-    return "validated mesh nodes";
+    free(value); value = NULL;
+
+    bailout:
+  	  if (value) {free(value); value = NULL}
+	  return ret;
+    return NULL;
 }
