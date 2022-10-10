import osmium as osm

# osm_file = open("map.osm")

class OSMHandler(osm.SimpleHandler): 
    def __init__(self): 
        osm.SimpleHandler.__init__(self) 
        self.h_data = []

    def way(self, w): 
        if w.tags.get('highway') == 'residential' and 'name' in w.tags:
            self.h_data.append(w.tags['name']) 


osmhandler = OSMHandler() 
osmhandler.apply_file("map.osm") 

osmhandler.h_data = list(dict.fromkeys(osmhandler.h_data))

h_russian = 'улица'
for i in range(0, len(osmhandler.h_data)):
    if h_russian in osmhandler.h_data[i].lower():
        osmhandler.h_data[i] = (osmhandler.h_data[i].replace('улица', '')).strip()
        

print(osmhandler.h_data)
print(osmhandler.h_count)
#data_colnames = ['type', 'tagkey', 'tagvalue'] 
#df_osm = pd.DataFrame(osmhandler.osm_data, columns=data_colnames) 
#df_osm = df_osm[df_osm["type"] == "way"] 
#df_osm = df_osm[df_osm["tagkey"] == "name"] 
