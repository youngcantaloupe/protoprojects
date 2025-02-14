import csv
from datetime import datetime
import matplotlib.pyplot as plt


def parse_job_data(file_path):
    """
    Function reads job data CSV files

    @param file_path: /path/to/file.csv
    @return job_data: A dictionary with key=year, value=list of monthly values
    """
    job_data = []
    with open(file_path, "r") as file:
        reader = csv.reader(file)
        header = None  # placeholder for col headers
        for index, row in enumerate(reader):
            if index == 5:  # skip metadata, set header
                header = row
            elif index > 5:  # parse data after row 5
                year = int(row[0])
                for month_idx, value in enumerate(row[1:], start=1):
                    if value.strip():
                        month = datetime(year, month_idx, 1)
                        job_data.append({"date": month, "jobs": int(value)})

    # print(job_data[:5], "\n")
    return job_data


def parse_presidents(file_path):
    """ """
    presidents = []
    with open("Presidents.csv", "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            row["term start"] = datetime.strptime(row["term start"], "%Y/%m/%d")
            row["term end"] = datetime.strptime(row["term end"], "%Y/%m/%d")
            presidents.append(row)
    return presidents


def merge_data(job_data, presidents):
    for entry in job_data:
        date = entry["date"]
        has_president = False

        for president in presidents:
            if president["term start"] <= date <= president["term end"]:
                entry["president"] = president["name"]
                entry["party"] = president["party"]
                has_president = True
                break

        if not has_president:
            entry["president"] = ""
            entry["party"] = ""


def calculate_party_contributions(job_data):
    # Initialize contributions dictionary
    contributions = {"Republican": 0, "Democratic": 0}

    # Track the previous party and its last job count
    previous_party = None
    previous_jobs = None

    for entry in job_data:
        current_party = entry["party"]
        current_jobs = entry["jobs"]

        if previous_party is not None:
            contributions[previous_party] += current_jobs - previous_jobs

        previous_party = current_party
        previous_jobs = current_jobs

    print(contributions.items())
    return contributions


def plot_job_trends(job_data, graph_name):
    graph_name += "party_job_trends.png"
    party_colors = {"Democratic": "blue", "Republican": "red"}

    # Group data by president
    grouped_data = {}
    for entry in job_data:
        president = entry["president"]
        if president not in grouped_data:
            grouped_data[president] = {"party": entry["party"], "dates": [], "jobs": []}
        grouped_data[president]["dates"].append(entry["date"])
        grouped_data[president]["jobs"].append(entry["jobs"])

    # Create a single figure for all presidents
    plt.figure(figsize=(12, 6))

    # Plot each president's data with the respective party color
    for president, data in grouped_data.items():
        party = data["party"]
        plt.plot(
            data["dates"],
            data["jobs"],
            label=f"{president} ({party})",
            color=party_colors.get(party, "gray"),
        )

    plt.title("Employment Trends Over Time by President and Party")
    plt.xlabel("Date")
    plt.ylabel("Employment (Thousands)")
    plt.legend(title="President (Party)", loc="upper left", bbox_to_anchor=(1, 1))
    plt.grid(True, linestyle="--", alpha=0.7)
    plt.tight_layout()
    plt.savefig(graph_name, dpi=300, bbox_inches="tight")
    plt.close()


def plot_job_data_differences(job_data_1, job_data_2):
    # Ensure both datasets are sorted by date
    job_data_1.sort(key=lambda x: x["date"])
    job_data_2.sort(key=lambda x: x["date"])

    # Compute differences
    dates = [entry["date"] for entry in job_data_1]
    differences = [
        entry_1["jobs"] - entry_2["jobs"]
        for entry_1, entry_2 in zip(job_data_1, job_data_2)
    ]

    # Plot differences
    plt.figure(figsize=(12, 6))
    plt.plot(dates, differences, label="Job Data Differences", color="purple")
    plt.axhline(0, color="black", linestyle="--", linewidth=1)
    plt.title("Differences Between Job Data 1 and Job Data 2")
    plt.xlabel("Date")
    plt.ylabel("Employment Difference (Thousands)")
    plt.grid(True, linestyle="--", alpha=0.7)
    plt.legend()
    plt.tight_layout()
    plt.savefig("job_data_differences.png", dpi=300, bbox_inches="tight")
    plt.close()


def plot_party_contribution(contributions, graph_name):
    graph_name += "party_job_contributions.png"
    # Prepare data for plotting
    parties = list(contributions.keys())
    values = list(contributions.values())

    # Plotting logic as before
    plt.figure(figsize=(8, 6))
    plt.bar(
        parties, values, color=["blue" if p == "Democratic" else "red" for p in parties]
    )
    plt.title("Total Contribution to Employment Growth by Party")
    plt.xlabel("Political Party")
    plt.ylabel("Employment Growth (Thousands)")
    plt.grid(axis="y", linestyle="--", alpha=0.7)
    plt.tight_layout()
    plt.savefig(graph_name, dpi=300, bbox_inches="tight")
    plt.close()


def main():
    provided_BLS_csv = "BLS_private_p7.csv"
    corrected_BLS_csv = "BLS_private_p7_corrected.csv"
    presidents_csv = "Presidents.csv"

    data_ext_provided = "provided_"
    data_ext_current = "corrected_"

    provided_job_data = parse_job_data(provided_BLS_csv)
    current_job_data = parse_job_data(corrected_BLS_csv)

    presidents = parse_presidents(presidents_csv)

    merge_data(provided_job_data, presidents)
    merge_data(current_job_data, presidents)
    party_contributions = calculate_party_contributions(provided_job_data)
    party_contributions = calculate_party_contributions(current_job_data)

    plot_job_trends(provided_job_data, data_ext_provided)
    plot_job_trends(current_job_data, data_ext_current)
    plot_job_data_differences(provided_job_data, current_job_data)
    plot_party_contribution(party_contributions, data_ext_provided)
    plot_party_contribution(party_contributions, data_ext_current)


if __name__ == "__main__":
    main()

    # for i, entry in enumerate(job_data_1[:5], start=1):
    #     print(f"Entry {i}: Date={entry['date'].year}, {entry['date'].month} Jobs={entry['jobs']}, President={
    #           entry['president']}, Party={entry['party']}")
