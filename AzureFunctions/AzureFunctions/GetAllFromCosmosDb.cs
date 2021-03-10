using System;
using System.IO;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Extensions.Http;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Logging;
using Newtonsoft.Json;
using System.Collections.Generic;

namespace AzureFunctions
{
    public static class GetAllFromCosmosDb
    {
        [FunctionName("GetAllFromCosmosDb")]
        public static async Task<IActionResult> Run(
            [HttpTrigger(AuthorizationLevel.Anonymous, "get", Route = null)] HttpRequest req,
            [CosmosDB(
                databaseName:"IOT20",
                collectionName: "Messages",
                ConnectionStringSetting = "CosmosDbConnection",
                SqlQuery ="SELECT * FROM c"
            )]IEnumerable<dynamic> cosmos,
            ILogger log)
        {
            log.LogInformation("HTTP triggered function executed.");

            return new OkObjectResult(cosmos);
        }
    }
}
