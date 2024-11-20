import json

# four types to print- f"{variable}"; "%s" % (variable); "{}".format(variable); " ", variable, " "
for er in range(1,2):
    for ir in range(1,3):
        for trial in range(1,6):
            file_name = f"494_bus_gauss_0.0{er}_0.0{ir}.mtx_{trial}.json"
            try:
                with open(file_name, 'r') as file:
                    data = json.load(file)
                    for line in data:
                        if "event" in line: 
                            print(line["event"])
            except json.JSONDecodeError:
                print(f"Error decoding json in {file_name}")
            except FileNotFoundError:
                print(f"{file_name} not found")
